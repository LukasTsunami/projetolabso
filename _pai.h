
pai (int readfd, int writefd)
{
  int nivel2 = 0; //variável responsável por entrar no "nível 2", ao ganhar a shell 
                //a idéia é usar ela como mutex depois
  pthread_t pth;	// this is our thread identifier
  int i = 0;

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
        
        if(nivel2==1){
            printf("\nParabens! Voce conseguiu ganhar a shell com sucesso!\n----------------------------------------------------\n\n");
        }
        if(nivel2==2){
            printf("\nPrint Screen tirado com sucesso!\n--------------------------------\n\n");
        }
        if(nivel2==3){
            x = 0;
            printf("\nTimer zerado com sucesso!\n--------------------------\n\n");
        }
        printf("Aperte a tecla referente a funcao que deseja utilizar: \n");
        
        printf("\n[0] - Voltar");
        printf("\n[1] - Tirar print screen da tela");
        printf("\n[2] - Zerar Timer");
        printf("\n[9] - Sair");
        printf("\n\nTempo decorrido = %d \n\n",x);
        system("sleep 1");
    }

  }

  printf("Saiu do While PAI");

}
