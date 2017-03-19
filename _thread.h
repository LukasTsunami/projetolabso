#include <pthread.h>

void *threadFunc(void *nivel2)
{
    int c,i = 0;
    char t;

    desconsideraEnter();
    while((c=getchar())!= 'e'){      

    int *aux_nivel = (int*)nivel2; //como vem um ponteiro de void, 
                                   //precisamos fazer o cast pra poder trabalhar com o mesmo
    
        if(c=='s'){
            printf("\nGanhando a shell, aguarde!\n");
            *aux_nivel = 1;
        }else if(c=='1'){
            printf("\n sorria pro print! :D\n");
            *aux_nivel = 2;
        }else if(c=='2'){
            printf("\nAjustando engrenagens do relógio!\n");
            *aux_nivel = 3;
        }else if(c=='0'){
            printf("\nVoltando para tela de monitoramento... aguarde!\n");
            *aux_nivel = 0;
        }else if(c=='9'){
            printf("\nfinalizando...\n\n");
            exit(1);
        }                 
    }

    return 0;


	return NULL;
}
