#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <stdio.h>

#define TAM_STR 100

char *lerLinha();

/* Tenta abrir o arquivo bin�rio, se n�o for poss�vel tenta criar um novo;
   Retorna NULL em caso de erro e um arquivo caso contr�rio.
*/
FILE* iniciarArquivo(const char *diretorio);

/* L� o labirinto
   Retorna NULL em caso de erro ou o labririnto alocado caso contr�rio
*/
char **lerLabirinto(char *nome,int *linha,int *coluna);

#endif // ARQUIVO_H_INCLUDED
