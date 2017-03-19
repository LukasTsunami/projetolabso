#include <pthread.h>

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
