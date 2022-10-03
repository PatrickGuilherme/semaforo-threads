#include "semaphoreswindows.h" 
#include <time.h>              //necessário p/ função time()
#include <stdlib.h>            // necessário p/ as funções rand() e srand()

// Variaveis globais
extern t_fila * raiz;
extern t_fila * aux;
extern t_fila * auxAnt;
extern int sequenciaArquivo;
extern int pos;

extern LONG lInsArqTId;
extern LONG lImpArqTId;

extern HANDLE mutex;			// mutex - Semáforo Binário {0, 1}
extern HANDLE posicoesOcupadas;	// Semáforos Sincronizadores de eventos
extern HANDLE posicoesLivres;	// Semáforos Sincronizadores de eventos

//Inserir arquivo
void insereArquivo() {
	t_fila * novo;
	while(1) {
		
		DOWN(posicoesLivres);
		LOCK(mutex); //Trava a RC
        Sleep(150);
		srand(time(NULL));
		
		//GERADOR DE DECISÃO
		int acao = rand() % 2;//1:remove | 0:insere

		if(acao == 0){
			printf("\n|=================== ADICIONAR ===================|");

			novo = (t_fila *) malloc(sizeof(t_fila));
			novo->prox = NULL;
	
			geraNomeArquivo(novo->Arquivo);
			aux = raiz;
			if (raiz == NULL)
	        {
				raiz = novo;
			}
			else
	        {
				while(aux->prox != NULL) {
					aux= (t_fila *) aux->prox;
				}
				aux->prox = novo;
			}
			pos++;//incrementa posicoes ocupadas
	
	        printf("\n[Informacao] Elemento adicionado com valor = %s\n", novo->Arquivo);	
		}else{
			printf("\n|==================== REMOVER ====================|");
						
			aux = raiz;
			if (raiz != NULL)
	        {
	        	int contAux;
	        	if(aux->prox != NULL) {
					raiz = aux->prox;
				}else{
					raiz = NULL;
				}
				printf("\n[Informacao] Elemento removido com valor = %s\n", aux->Arquivo);
			}else{
				printf("\n[Mensagem] Sem valores a remover\n");
			}
		}
	
		UNLOCK(mutex);//Libera a RC
        Sleep(1);
		UP(posicoesOcupadas);
	}
}

//Exibir dados
void imprimeArquivo() {
	while(1) {
		DOWN(posicoesOcupadas);  //Elimina a Espera Ocupada
		LOCK(mutex);   //Trava a RC
		printf("\n|==================== EXIBIR =====================|");
		Sleep(200); // Simula o tempo de impressão
		aux = raiz;
		if(aux != NULL){
			while(aux != NULL){
				printf("\n[Informacao] Item com valor = %s \n", aux->Arquivo);
				aux = aux->prox;		
			}
		}else{
			printf("\n[Mensagem] Sem valores a exibir\n");
		}
		
		free(aux);
		UNLOCK(mutex);  //Libera a RC
		UP(posicoesLivres);
		Sleep(2); // Simula o tempo de impressão
	}
}

//Gerar nome do arquivo
void geraNomeArquivo(char *string) {
    char *tmp;
	char seq[10];

    tmp = string;

	strcpy(tmp, "Arquivo ");
	itoa(sequenciaArquivo++, seq, 10);
	strcat(tmp, seq);
}

//
void DOWN(HANDLE h) {
	WaitForSingleObject(h, INFINITE);
}

//UP
void UP(HANDLE h) {
	ReleaseSemaphore(h, 1, NULL);
}

//TRAVA
void LOCK(HANDLE h) {
	WaitForSingleObject(h, INFINITE);
}

//DESTRAVA
void UNLOCK(HANDLE h) {
    ReleaseMutex(h);
}


