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
  pthread_t pth;  	// identificador da thread
  pthread_create(&pth,NULL,threadFunc,&controle);

  while(1)
  {
    switch(controle)
    {
      case 9999:
        sprintf(enviaPorPipe, "%d", controle);
        strcat(enviaPorPipe, "\n");
      break;

      case -1:
        sprintf(enviaPorPipe, "%d", controle);
        strcat(enviaPorPipe, "\n");

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

      break;

      case 0:
        sprintf(enviaPorPipe, "%d", controle);
        strcat(enviaPorPipe, "\n");

      break;

      case 1:
      		system("import -window root tela.png");
          controle = 0;
      break;

      case 2:
      	novaJanela();
        controle = 0;
      break;

      default:
      break;
      }
      write(writefd, enviaPorPipe, BUFFPIPE);
      }
}
