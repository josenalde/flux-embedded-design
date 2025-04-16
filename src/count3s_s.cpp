#include <iostream>
#include <cstdlib>
#include <ctime>
//ESTE É O CÓDIGO TOTALMENTE SERIAL. ESTOU NO VSCODE NO WINDOWS 11
//MEU PROCESSADOR É Intel® Core™ i7-10510U, quad core, com 2 threads por core
#define MAX 1000000
#define RUNS 10 //ESTOU EXECUTANDO 10 VEZES. EMBORA NO SERIAL OS RESULTADOS SEJAM INTERESSANTES, AO USARMOS THREADS, NÃO RECOMENDO
// PERMANECER NO WINDOWS, POIS DE FATO OS SISTEMAS EMBARCADOS SERÃO NO MÍNIMO ALGUMA DISTRO DE LINUX EMBARCADO
// ASSIM, VOU COMPILAR OS CÓDIGOS E TESTAR PARA ENTREGAR A TAREFA 100% NO LINUX. VOU USAR O UBUNTU QUE TENHO INSTALADO NA WSL
// O SUBSISTEMA DO WINDOWS PARA LINUX. SE USAR LINUX, RODE DIRETO OS CÓDIGOS NO LINUX. SE USAR WINDOWS, no terminal como administrador
// INSTALA COM  wsl --install. POR PADRÃO É UBUNTU, MAS VER DOCUMENTAÇÃO DO WSL NO SITE DA MICROSOFT SE QUISER OUTRAS DISTROS
// ATENÇÃO PARA VER SE O RECURSO WSL ESTÁ HABILITADO NO SEU WINDOWS
int v[MAX];
int length = MAX;
int count;
double sumTimings = 0;

using namespace std;

int count3s();

int main() {
    srand(time(NULL));
    cout.precision(6);
    
    for (int i = 0; i < RUNS; i++) {
        for (int i=0; i<length; i++) {
            v[i] = rand() % 4;
        }
        cout << endl << count3s() << " found at RUN " << i+1 << endl;
    }
    cout << "Average Time: " << sumTimings/RUNS << endl;
    return 0;
}

int count3s() {
    int i;
    count=0;
    clock_t tstart, tend;
    tstart = clock(); //tempo de cpu (cpu time), não inclui delays nem espera de IO
    for(i=0;i<length;i++) {
        if(v[i]==3) count++;
    }
    tend = clock();
    double trun;
    trun = (double)(tend - tstart)/(double)CLOCKS_PER_SEC;
    sumTimings += trun;
    cout << fixed << "Time: " << trun << endl;
    return count;
}