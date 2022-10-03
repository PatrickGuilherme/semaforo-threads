#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#ifndef SEMAPHORES_H
#define SEMAPHORES_H 1

#define POSICOES 100

typedef struct {
	char Arquivo[100];
	void * prox;
} t_fila ;


// Prototipos
void insereArquivo();
void imprimeArquivo();
void geraNomeArquivo(char *);

/**
Operações sobre semáforos contadores
*/
void DOWN(HANDLE);
void UP(HANDLE);
void LOCK(HANDLE);
void UNLOCK(HANDLE);

#endif

