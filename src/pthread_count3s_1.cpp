//CONTAGEM DE 3s COM THREADS, PORÉM SEM CONTROLE DE REGIÃO CRÍTICA, CONTAGEM NÃO É SEGURA, POIS count GLOBAL É COMPARTILHADA PELAS T THREADS
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

using namespace std; //PARALELO COM 8 THREADS, SEM MUTEX

//#define N 32
#define N 1000000

/*Processador Intel® Core™ i7-10510U quad-core com 2 threads por core: 
  Núcleo é um termo de hardware que descreve o número de unidades de processamento central independentes em um único componente de 
  computação (matriz ou chip).
  Um thread, ou thread de execução, é um termo de software para a sequência básica ordenada de instruções que pode ser passada
  ou processada por um único núcleo de CPU.
*/
#define T 8 //máximo para a CPU em questão

int v[N], count;

void* count3s_thread(void* id) {
    long my_id = (long) id;
    cout << "thread " << my_id;
    pthread_t thId = pthread_self();
    printf(" with ID: %ld\n", thId);
    int length_per_thread = N/T;
    int start = my_id*length_per_thread;
    for (int i=start; i<start+length_per_thread;i++) {
        if (v[i] == 3) count++;
    }
    return NULL; //evita warning
}

int main()  {
    pthread_t tid[T]; //array de threads
    int err;
    //semente para o gerador de números aleatórios (timestamp unix)
    srand(time(NULL));
    
    for (int i=0; i<N; i++) {
        v[i] = rand() % 4;
        //cout << v[i] << ",";
    }
    cout << "\n";
    clock_t tstart, tend;
    tstart = clock();
    for (long i=0; i<T; i++) {
        err = pthread_create(&tid[i], NULL, count3s_thread, (void*) i);
    }
    for (int i=0; i<T; i++) {
        err  = pthread_join(tid[i], NULL);
    }
    tend = clock();
    double trun;
    trun = (double)(tend - tstart)/(double)CLOCKS_PER_SEC;
    cout.precision(12);
    cout << fixed << "Time: " << trun << endl;
    cout << endl << count << " found";
    return 0;
}
