#include <stdio.h>
#include <stdlib.h>
#include "Arquivo.h"
#include "Estruturas.h"

int main(){
    char **lab;
    int l,c,linha,coluna;

    tipo_nodo_visitados *nodo_visitados;
    lista lista;

    lab = lerLabirinto("teste.txt",&linha,&coluna);

    if(!lab)
      printf("\n> Erro na leitura.");
    else{
      printf("\n");
      for( l=0 ; l<linha ; l++ ){
         for( c=0 ; c<coluna ; c++)
            printf("%c",lab[l][c]);
         printf("\n");
      }
      for( l=0 ; l<linha ; l++ )
         free(lab[l]);
      free(lab);

    }


    return 0;
}
