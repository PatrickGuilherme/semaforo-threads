#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#ifndef SEMAPHORES_H
#define SEMAPHORES_H 1

#define POSICOES 100

typedef struct {
	int Arquivo;
	void * prox;
} t_fila ;


// Prototipos
void insereArquivo();
void imprimeArquivo();
int geraNomeArquivo();

/**
Operações sobre semáforos contadores
*/
void DOWN(HANDLE);
void UP(HANDLE);
void LOCK(HANDLE);
void UNLOCK(HANDLE);

#endif

