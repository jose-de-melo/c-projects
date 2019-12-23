#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <stdio.h>

#define TAM_STR 100

char *lerLinha();

/* Tenta abrir o arquivo binário, se não for possível tenta criar um novo;
   Retorna NULL em caso de erro e um arquivo caso contrário.
*/
FILE* iniciarArquivo(const char *diretorio);

/* Lê o labirinto
   Retorna NULL em caso de erro ou o labririnto alocado caso contrário
*/
char **lerLabirinto(char *nome,int *linha,int *coluna);

#endif // ARQUIVO_H_INCLUDED
