#define BUFFPIPE 10000 // BUFFER TOTAL DO PIPE A SER ENVIADO PARA O PAI
#define BUFF 1024   //BUFFER PARA SYSTEM'S CALL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include "_thread.h"
#include "_novaJanela.h"
#include "_pai.h"
#include "_filho.h"
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


