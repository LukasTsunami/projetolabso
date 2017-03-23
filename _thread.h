#include <pthread.h>
#include "_desconsideraEnter.h"

void *threadFunc(void *controleTela)
{
    int c; //character que vai ser lido do buffer
    
    int *aux_controle = (int*)controleTela;

    desconsideraEnter();
    while((c=getchar())!= 'e'){      

        switch(c)
        {
            case 's':                
                *aux_controle = 0;
                break;
            
            case 'v':
                *aux_controle = -1;
                break;

            case '1':    
                *aux_controle = 1;
                break;

            case '2':
                *aux_controle = 2;
                break;
            
            case '3':
                *aux_controle = 3;
                break;

            case '4':
		*aux_controle = 4;
		break;

            case '\e':
                exit(1);
                break;

            default:
                break;
        } 
    }

    return 0;


	return NULL;
}
