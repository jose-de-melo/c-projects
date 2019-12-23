#include <string.h>
#include <stdlib.h>
#include "Arquivo.h"

/* Lê o labirinto
   Retorna NULL em caso de erro ou o labririnto alocado caso contrário
*/
char **lerLabirinto(char *nome,int *linha,int *coluna){
   FILE *f;
   char **lab,caractere,str[TAM_STR];
   int c,l;

   f = iniciarArquivo(nome);

   if(!f)
      return NULL;

   // Verifica se arquivo está vazio
   fseek(f,0,SEEK_END);
   if(!ftell(f))
      return NULL;

   // Retorna para o início do arquivo
   fseek(f,0,SEEK_SET);

   // Limpa o array de str
   memset(str,'\0',TAM_STR);

   // Lê o número de linhas
   caractere = fgetc(f);
   while(caractere != '\n' && caractere != ';' && caractere != EOF){
      // insere o caractere na string
      str[strlen(str)] = caractere;
      str[strlen(str)] = '\0';
      caractere = fgetc(f);
   }
   *linha = atoi(str);

   // Limpa o array de str
   memset(str,'\0',TAM_STR);

   // Lê o número de colunas
   caractere = fgetc(f);
   while(caractere != '\n' && caractere != ';' && caractere != EOF){
      // insere o caractere na string
      str[strlen(str)] = caractere;
      str[strlen(str)] = '\0';
      caractere = fgetc(f);
   }
   *coluna = atoi(str);

   // Verifica se ambos, linha e colula, foram lidos.
   if (!(*linha) || !(*coluna))
      return NULL;

   // Aloca o espaço para a estrutura do labirinto
   lab = (char **)malloc(sizeof(char*)*(*linha));

   // Verifica se as linhas foram alocadas
   if(!lab)
      return NULL;

   // Aloca as colunas
   for(l = 0; l < (*linha); l++)
      lab[l] = (char *)malloc(sizeof(char)*(*coluna));

   // Verifica se as colunas foram alocadas
   if(!(*lab)){
      free(lab);
      return NULL;
   }

   fgets(str,TAM_STR,f); // pula para a primeira linha da matriz
   fgets(str,TAM_STR,f); // Lê a primeira linha da matriz

   for(l = 0; l < (*linha); l++){
      for(c = 0 ; c < (*coluna) ; c++ )
         lab[l][c] = str[c];
      fgets(str,TAM_STR,f); // Lê a proxima linha
   }
   printf("\nLabirinto [%s] de %d linhas e %d colunas\n\nPressione qualquer tecla para continuar...",nome,*linha,*coluna);
   _getche();
   if(l != (*linha) || c != (*coluna) ){ // Erro na leitura, faltando informações no arquivo
      for(l = 0 ; l < (*linha) ; l++)
         free(lab[l]);
      free(lab);
      return NULL;
   }

   fclose(f);
   return lab;
}

/* Tenta abrir o arquivo binário, se não for possível tenta criar um novo;
   Retorna NULL em caso de erro e um arquivo caso contrário.
*/
FILE* iniciarArquivo(const char *diretorio){
   FILE *a;

   // Abre o arquivo para leitura
   a = fopen(diretorio,"r+");

   return a;
}
