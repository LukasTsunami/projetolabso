pai (int readfd, int writefd)
{
	char PIPERecebido[BUFFPIPE];
	char *informacoes;
	char *hostname;
	char *iplocal;
	char *memUsed;
	char *memTotal;
	char *cpuUsage;

	while(1)
	{
		system("clear");
        	read(readfd,PIPERecebido,BUFFPIPE);
		if ( controleDeTela == 0 )
		{
			informacoes = strtok(PIPERecebido, "\n");
			hostname = informacoes;
			iplocal = strtok(NULL,"\n");
			memUsed = strtok(NULL,"\n");
			memTotal = strtok(NULL,"\n");
			cpuUsage = strtok(NULL,"\n");

			printf("Hostname\tIP-Local\tMemoria Utilizada/Total\t\tCPU\n");
			printf("%s\t\t%s\t\t%s/%s MBs\t\t%s%\n",hostname,iplocal,memUsed,memTotal,cpuUsage);
			printf("\n\n\n\n\n\n\n\n\n\t\tPressione a tecla [S] para menu de opcoes\n");
			informacoes = NULL;	
			system("sleep 0.6");        
		}
		
		if ( controleDeTela == 1)
		{
			printf("Aperte a tecla referente a funcao que deseja utilizar: \n");        
			printf("\n[V] - Voltar");
			printf("\n[1] - Tirar print screen da tela");
			printf("\n[2] - Zerar Timer");
			printf("\n[3] - Abrir nova janela de terminal com o TOP carregado");
			printf("\n[4] - Abrir uma SHELL");
			printf("\n[ESC] - Sair");
			printf("\n\nTempo decorrido = %d \n\n",x);
			system("sleep 1");
		}
   	
	}
}
