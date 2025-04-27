#include <pthread.h>
#include <iostream>
#include <unistd.h>

//limite de threads em Linux definda em /proc/sys/kernel/threads-max
/*Rotina que será executada pelas duas threads*/
void * routine(void *arg);
 
int main (int argc, char *argv[]) {
    pthread_t thread_A;
    pthread_t thread_B;

    void * thread_res;
    int rstatus;
    
    /*tenta iniciar o thread, indicando a função 'routine' e passando como argumento a string "Thread A"*/
    rstatus = pthread_create (&thread_A, NULL, routine, (void*)("Thread A"));
 
    /*verificar se ocorreu algum erro na chamada de pthread_create*/
    if(rstatus != 0) {
        std::cout << "Erro ao criar a thread A.\n";
        exit(EXIT_FAILURE);
    }
 
    std::cout << "Thread A criada com sucesso!\n";
 
    /*tenta iniciar o thread, indicando novamente a função 'routine' e passando como argumento a string "Thread B"*/
    rstatus = pthread_create (&thread_B, NULL, routine, (void*)("Thread B"));
 
    /*verificar se ocorreu algum erro na chamada de pthread_create*/
    if(rstatus != 0) {
        std::cout << "Erro ao criar a thread B.\n";
        exit(EXIT_FAILURE);
    }
 
    std::cout << "Thread B criada com sucesso!\n";
  
    /*aguarda finalização do thread A identificado por thread_A. O retorno é passado pelo ponteiro thread_res*/
    rstatus = pthread_join (thread_A, &thread_res);
    if(rstatus != 0) {
        std::cout << "Erro ao aguardar finalização do thread A.\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Thread A finalizada! Retorno = " << (char *)thread_res;
  
    /*aguarda finalização do thread B identificado por thread_idB. O retorno é passado pelo ponteiro thread_res*/
    rstatus = pthread_join (thread_B, &thread_res);
    if(rstatus != 0) {
        std::cout << "Erro ao aguardar finalização do thread B.\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Thread B finalizada! Retorno = " << (char *)thread_res;
    return 0;
}
 
void * routine(void *arg) {
    int contador = 10;
    while(contador--) {
        std::cout << (char *)arg <<  ":" << contador << std::endl;
        usleep(100); // no windows Sleep
        //sched_yield(); //bloqueia atual, que vai para ready. A outra que está na fila e estava ready entra em execução
    }
    /*finaliza a função retornando o argumento que foi recebido*/
    pthread_exit(arg);
    return NULL;
}