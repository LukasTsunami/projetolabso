#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFPIPE 10000 // BUFFER TOTAL DO PIPE A SER ENVIADO PARA O PAI
#define BUFF 1024   //BUFFER PARA SYSTEM'S CALL

int main(){

  int	descritor,  // usado para criar o processo filho pelo fork
	pipe1[2],  // comunicacao pai -> filho
	pipe2[2];  // comunicacao filho -> pai

   if (pipe(pipe1)<0 || pipe(pipe2) <0)
	{
    printf("Erro na chamada PIPE");
	  exit(0);
	}

   //   Fork para criar o processo filho

  if ( (descritor = fork()) <0)
	{
    printf("Erro na chamada FORK");
    exit(0);
  }


	else if (descritor >0)  // PROCESSO PAI
	   {
    close(pipe1[0]); // fecha leitura no pipe1
		close(pipe2[1]);  // fecha escrita no pipe2

		pai(pipe2[0], pipe1[1]);

		close(pipe1[1]); // fecha pipe1
		close(pipe2[0]);  // fecha pipe2
    printf("Processo pai encerrado!");
		exit(0);

	    } // FIM DO PROCESSO PAI

	else // PROCESSO FILHO
	{
    close(pipe1[1]); // fecha escrita no pipe1
		close(pipe2[0]);  // fecha leitura no pipe2

		filho(pipe1[0], pipe2[1]);

		close(pipe1[0]); // fecha leitura no pipe1
		close(pipe2[1]);  // fecha escrita no pipe2
    printf("Processo filho encerrado!");
		exit(0);

	}
}

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

  printf("Saiu do While PAI");

}


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

  while(1)
  {
    if((fp = popen(getHostname, "r")) == NULL)
     printf("ERROR 404");
    if(fgets(buff, BUFF, fp) == NULL)
      printf("ERROR 404");

    strcat(enviaPorPipe, buff);

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
  }

}
