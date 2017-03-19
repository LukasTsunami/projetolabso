#include <pthread.h>

void *threadFunc(void *nivel2)
{
    int c; //character que vai ser lido do buffer
    
    int *aux_nivel = (int*)nivel2; //como vem um ponteiro de void, 
                                   //precisamos fazer cast p/ poder trabalhar com ele
    
    desconsideraEnter();
    while((c=getchar())!= 'e'){      

        switch(c)
        {
            case 's':
                printf("\nGanhando a shell, aguarde!\n");
                *aux_nivel = 1;
                break;
            
            case '0':
                printf("\nVoltando para tela de monitoramento... aguarde!\n");
                *aux_nivel = 0;
                break;

            case '1':    
                printf("\n sorria pro print! :D\n");
                *aux_nivel = 2;
                break;

            case '2':
                printf("\nAjustando engrenagens do relógio!\n");
                *aux_nivel = 3;
                break;
            
            case '\e':
                printf("\nfinalizando...\n\n");
                exit(1);
                break;

            default:
                break;
        } 
    }

    return 0;


	return NULL;
}
