
filho(int readfd,int writefd)
{
  char *getHostname = "cat /etc/hostname"; //Recupera o Hostname
  char *getIPLocal = "hostname -I"; //Recupera o IP Local
  char *getMemUsed = "free -m | head -n 2 | tail -n 1 | awk '{print $3}'"; // Memoria usada em MEGABYTES
  char *getMemTotal = "free -m | head -n 2 | tail -n 1 | awk '{print $2}'"; //Memoria Total em MEGABYTES
  char *getCPUusage= "top -n 1 | head -n 3 | tail -n 1 | awk '{print $2}'"; //CPU usado em %
  char *buff[BUFF];
  char enviaPorPipe[BUFFPIPE];
  FILE *fp;

  int controle = -1;
  pthread_t pth;	// identificador da thread

  int tira_apenas_um_print_screen_por_vez = 0; //vai precisar de mutex
  int abre_apenas_uma_janela = 0;

  pthread_mutex_t mutexPrint;
  pthread_mutex_init(&mutexPrint,NULL);  
  pthread_mutex_t mutexAbreNovaJanela;
  pthread_mutex_init(&mutexAbreNovaJanela,NULL);  
 
  pthread_create(&pth,NULL,threadFunc,&controle);


  while(1)
  {
   switch(controle)
   {
	case -1:    
		if((fp = popen(getHostname, "r")) == NULL)
		printf("ERROR 404");
		if(fgets(buff, BUFF, fp) == NULL)
		printf("ERROR 404");

		strcat(enviaPorPipe, buff);
		strcat(enviaPorPipe, "\n");
		pclose(fp);


		if((fp = popen(getIPLocal, "r")) == NULL)
		printf("ERROR 404");
		if(fgets(buff, BUFF, fp) == NULL)
		printf("ERROR 404");

		strcat(enviaPorPipe, buff);
		pclose(fp);

		if((fp = popen(getMemUsed, "r")) == NULL)
		printf("ERROR 404");
		if(fgets(buff, BUFF, fp) == NULL)
		printf("ERROR 404");

		strcat(enviaPorPipe, buff);
		pclose(fp);

		if((fp = popen(getMemTotal, "r")) == NULL)
		printf("ERROR 404");
		if(fgets(buff, BUFF, fp) == NULL)
		printf("ERROR 404");

		strcat(enviaPorPipe, buff);
		pclose(fp);

		if((fp = popen(getCPUusage, "r")) == NULL)
		printf("ERROR 404");
		if(fgets(buff, BUFF, fp) == NULL)
		printf("ERROR 404");

		strcat(enviaPorPipe, buff);
		pclose(fp);


		write(writefd, enviaPorPipe, BUFFPIPE);
		enviaPorPipe[0] = '\0';
	break;
    
	case 1:
		if(tira_apenas_um_print_screen_por_vez == 0)
		{
			system("import -window root tela.png");
			pthread_mutex_lock(&mutexPrint);
			    tira_apenas_um_print_screen_por_vez = 1;
			pthread_mutex_unlock(&mutexPrint);
		}

		else
		{
		if(tira_apenas_um_print_screen_por_vez!=0)
		{
			pthread_mutex_lock(&mutexPrint);
			    tira_apenas_um_print_screen_por_vez = 0;
			pthread_mutex_unlock(&mutexPrint);
		}
		}
	break;

        case 2:
            x = 0;
        break;

        case 3:
		if(abre_apenas_uma_janela==0){
		novaJanela();
		}

		pthread_mutex_lock(&mutexAbreNovaJanela);
		abre_apenas_uma_janela = 1;
		pthread_mutex_unlock(&mutexAbreNovaJanela);
        break;

	default:
	break;
  }
}
}
