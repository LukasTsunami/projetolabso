#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  


#define BUFFPIPE 10000 // BUFFER TOTAL DO PIPE A SER ENVIADO PARA O PAI
#define BUFF 1024   //BUFFER PARA SYSTEM'S CALL

int nivel2 = 0;

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

void desconsideraEnter(){
    static struct termios oldt, newt;

        /*tcgetattr gets the parameters of the current terminal
        STDIN_FILENO will tell tcgetattr that it should write the settings
        of stdin to oldt*/
        tcgetattr( STDIN_FILENO, &oldt);
        /*now the settings will be copied*/
        newt = oldt;

        /*ICANON normally takes care that one line at a time will be processed
        that means it will return if it sees a "\n" or an EOF or an EOL*/
        newt.c_lflag &= ~(ICANON);          

        /*Those new settings will be set to STDIN
        TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);

        /*This is your part:
        I choose 'e' to end input. Notice that EOF is also turned off
        in the non-canonical mode*/
    
    
}


void *threadFunc(void *arg)
{
    int c,i = 0;
    char t;

    desconsideraEnter();

    while((c=getchar())!= 'e'){      
        if(c=='s'){
            nivel2 = 1;
        }else if(c=='1'){
            printf("\n sorria pro print! :D\n");
            nivel2 = 2;
        }else if(c=='2'){
            printf("Ajustando engrenagens do relógio!");
            nivel2 = 3;
        }else if(c=='9'){
            printf("\nfinalizando...\n\n");
            exit(1);
        }                 
    }

    return 0;


	return NULL;
}


pai (int readfd, int writefd)
{

  pthread_t pth;	// this is our thread identifier
  int i = 0;

  pthread_create(&pth,NULL,threadFunc,"foo");
	
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
        printf("\n[1] - Tirar print screen da tela");
        printf("\n[2] - Zerar Timer");
        printf("\n[9] - Sair");
        printf("\n\nTempo decorrido = %d \n\n",x);
        system("sleep 1");
    }

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
