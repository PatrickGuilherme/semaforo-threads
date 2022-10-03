/**
    O programa simula uma fila de impress�o para experimentar 
    os semaforos binarios e contadores da API do Window
*/

#include "semaphoreswindows.h"
#include "functions.c"
// Variaveis globais
t_fila filaArquivos;

t_fila * raiz = NULL;
t_fila * aux;
t_fila * auxAnt;
int sequenciaArquivo = 0;
int pos = -1;


HANDLE hMainThrd;   // Handle para a Thread main 
HANDLE hInsArqThrd; // Handle para a Thread que Insere Arquivo
HANDLE hImp1ArqThrd;   // Handle para a Thread que imprime arquivo
HANDLE hImp2ArqThrd;   // Handle para a Thread que imprime arquivo
HANDLE hImp3ArqThrd;   // Handle para a Thread que imprime arquivo
HANDLE hImp4ArqThrd;   // Handle para a Thread que imprime arquivo

LONG   lInsArqTId;  
LONG   lImpArqTId; 

HANDLE mutex;				// mutex - Sem�foro Bin�rio {0, 1}
HANDLE posicoesOcupadas;	// Sem�foro contadore de eventos
HANDLE posicoesLivres;	// Sem�foro contador de eventos


int main(int argc, char **argv) {
	//Sem�for bin�rio - Chave da RC {0,1}
    mutex = CreateMutex(NULL,FALSE, "Fila_Mutex");
   
    // Testa se o mutex foi corretamente criado
    if (mutex == NULL)
	{
        printf("\nErro na cria��o do mutex: %d\n", GetLastError());
        ExitProcess(0);
    }

	//Sem�foro Contador usado para controle das posicoes ocupadas
	posicoesOcupadas = CreateSemaphore(NULL,0,POSICOES,"SEM_CHEIO");
    if (posicoesOcupadas == NULL)
    {
        printf("\nErro na cria��o do Sem�foro posicoesOcupadas: %d\n", GetLastError());
        ExitProcess(0);
    }

	//Sem�foro Contador usado para controle de posicoes livres
	posicoesLivres = CreateSemaphore(NULL,POSICOES,POSICOES,"SEM_LIVRE");
    if (posicoesLivres == NULL)
    {
        printf("\nErro na cria��o do Sem�foro posicoesLIvres: %d\n", GetLastError());
        ExitProcess(0);
    }

    // Cria as threads que usam o spool de impress�o
	hInsArqThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)insereArquivo,NULL,0,(LPDWORD) &lInsArqTId );
	
	hImp1ArqThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)imprimeArquivo,NULL,0,(LPDWORD) &lImpArqTId );
	hImp2ArqThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)imprimeArquivo,NULL,0,(LPDWORD) &lImpArqTId );
	hImp3ArqThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)imprimeArquivo,NULL,0,(LPDWORD) &lImpArqTId );
	hImp4ArqThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)imprimeArquivo,NULL,0,(LPDWORD) &lImpArqTId );

	printf("Suspendendo a Thread Main\n\n");
	// Essa � uma forma de bloquear uma thread indefinidamente
    hMainThrd = GetCurrentThread();
    SuspendThread(hMainThrd);
    exit(0);
}

