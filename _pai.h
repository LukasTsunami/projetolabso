
pai (int readfd, int writefd)
{
  int nivel2 = 0; //variável responsável por entrar no "nível 2", ao ganhar a shell 
                //a idéia é usar ela como mutex depois
  pthread_t pth;	// identificador da thread

  int tira_apenas_um_print_screen_por_vez = 0; //vai precisar de mutex
  int abre_apenas_uma_janela = 0;

  pthread_mutex_t mutexPrint;
  pthread_mutex_init(&mutexPrint,NULL);  
  
  pthread_mutex_t mutexAbreNovaJanela;
  pthread_mutex_init(&mutexAbreNovaJanela,NULL);  
  
  pthread_create(&pth,NULL,threadFunc,&nivel2);

  char PIPERecebido[BUFFPIPE];
  char *informacoes;
  char *hostname;
  char *iplocal;
  char *memUsed;
  char *memTotal;
  char *cpuUsage;

  int x=0;
  while(1)
  {
    x++;
    if(nivel2==0)
    {
        read(readfd,PIPERecebido,BUFFPIPE);
        informacoes = strtok(PIPERecebido, "\n");
        hostname = informacoes;
        iplocal = strtok(NULL,"\n");
        memUsed = strtok(NULL,"\n");
        memTotal = strtok(NULL,"\n");
        cpuUsage = strtok(NULL,"\n");

        printf("Hostname\tIP-Local\tMemoria Utilizada/Total\t\tCPU\n");
        printf("%s\t\t%s\t\t%s/%s\t\t%s\n",hostname,iplocal,memUsed,memTotal,cpuUsage);
        printf("\n\n\n\n\n\n\n\n\n\t\tPressione a tecla [S] para controlar\n");
        informacoes = NULL;

        system("sleep 0.6");
        system("clear");
    }
    else if(nivel2!=0)
    {        
        system("clear");
        
        if(nivel2==1)
        {
            printf("\nParabens! Voce conseguiu ganhar a shell com sucesso!\n----------------------------------------------------\n\n");
        }

        if(nivel2==2)
        {
            printf("\nPrint Screen tirado com sucesso!\n--------------------------------\n\n");
            if(tira_apenas_um_print_screen_por_vez == 0)
            {
                system("import -window root tela.png");
                pthread_mutex_lock(&mutexPrint);
                    tira_apenas_um_print_screen_por_vez = 1;
                pthread_mutex_unlock(&mutexPrint);
            }
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

        if(nivel2==3)
        {
            x = 0;
            printf("\nTimer zerado com sucesso!\n--------------------------\n\n");
        }

        if(nivel2==4)
        {
            printf("teste");
            if(abre_apenas_uma_janela==0){
                novaJanela();
            }

            pthread_mutex_lock(&mutexAbreNovaJanela);
                abre_apenas_uma_janela = 1;
            pthread_mutex_unlock(&mutexAbreNovaJanela);

        }

        printf("Aperte a tecla referente a funcao que deseja utilizar: \n");
        
        printf("\n[0] - Voltar");
        printf("\n[1] - Tirar print screen da tela");
        printf("\n[2] - Zerar Timer");
        printf("\n[3] - Abrir nova janela de terminal com o TOP carregado");
        printf("\n[ESC] - Sair");
        printf("\n\nTempo decorrido = %d \n\n",x);
        system("sleep 1");
    }

  }

  printf("Saiu do While PAI");

}
