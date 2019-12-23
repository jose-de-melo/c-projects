#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include "Arquivo.h"
#include "Estruturas.h"
#include "Labirinto.h"

int main(){
   char **lab,op,str[TAM_STR];
   int l,c,linha,coluna;

   setlocale(LC_ALL, "Portuguese");

   do{
      limpa_tela();
      printf("\t Labirinto\n\n Forneça o nome do arquivo: ");
      setbuf(stdin,NULL);
      fgets(str,TAM_STR,stdin);
      setbuf(stdin,NULL);
      if(str[0] == '\n'){
         printf("\n> O nome não pode ser vazio.\n\n Pressione qualquer tecla para continuar...");
         _getche();
         continue;
      }
      corrige_string(str);
      lab = lerLabirinto(str,&linha,&coluna);
      if(!lab)
        printf("\n\n> Erro ao na leitura do arquivo.");
      else{
         if(verificar_integridade(lab,linha,coluna))
            mover(lab,linha,coluna);
        else
            printf("\n\n> Erro na integridade do labirinto.");
      }
      op = menu();

   }while(op != '1');


   // Libera o espaço de memória reservado para a estrutura
   if(lab){
      for( l = 0 ; l<linha ; l++ )
         free(lab[l]);
      free(lab);
   }
   return 0;
}

/* Busca a próxima posição possível
   0 - Nenhuma
   1 - Direita
   2 - Esquerda
   3 - Baixo
   4 - Cima
*/
int direcao(char **lab,lista l,int linha, int coluna,int posL,int posC){
   tipo_elemento_visitados eVistados;
   int achou;

   // Direita
   if(lab[posL][posC+1] != 'x' && lab[posL][posC+1] != 'c' && posC+1 < coluna){
      eVistados.x = posL;
      eVistados.y = posC+1;
      achou = busca_elemento_lista(l,eVistados);
      if(achou == -1)
         return 1; // Direita
   }

   // Esquerda
   if(lab[posL][posC-1] != 'x' && lab[posL][posC-1] != 'c' && posC-1 > 0){
      eVistados.x = posL;
      eVistados.y = posC-1;
      achou = busca_elemento_lista(l,eVistados);
      if(achou == -1)
         return 2; // Esquerda
   }

   // Baixo
   if(lab[posL+1][posC] != 'x' && lab[posL+1][posC] != 'c' && posL+1 < linha){
      eVistados.x = posL+1;
      eVistados.y = posC;
      achou = busca_elemento_lista(l,eVistados);
      if(achou == -1)
         return 3; // Direita
   }

   // Cima
   if(lab[posL-1][posC] != 'x' && lab[posL-1][posC] != 'c' && posL-1 > 0){
      eVistados.x = posL-1;
      eVistados.y = posC;
      achou = busca_elemento_lista(l,eVistados);
      if(achou == -1)
         return 4; // Direita
   }

   return 0;
}

void mover(char **lab,int linha, int coluna){
   int posL,posC,l,c,bonus = 0,dir=0,num = 1;
   //tipo_nodo_visitados *nVisitados;
   //tipo_nodo_pilha *nPilha;
   tipo_elemento_visitados eVisitados;
   lista list = cria_lista();
   pilha p = cria_pilha();

   busca_inicio(lab,linha,coluna,&posL,&posC);

   // Insere o ínicio para posições ja movimentadas
   eVisitados.x = posL;
   eVisitados.y = posC;
   insere_final(list,eVisitados);

   // Limpa início
   lab[posL][posC] = ' ';

   // Movimentando pelo labirinto
   do{
      limpa_tela();
      printf("\t\t Labirinto[%d][%d]\n\n  ",posL,posC);

      // Imprime o labirinto atual
      for( l=0 ; l<linha ; l++){
         for ( c=0 ; c<coluna ; c++){

            if( l == posL && c == posC)
               printf("#");
            else
               printf("%c",lab[l][c]);
         }
         printf("\n  ");
      }
      printf("\n\n> Bonus: %d",bonus);
      //_getche();
      usleep(150000); // aguarda

      // Movimentos
      dir = direcao(lab,list,linha,coluna,posL,posC);
      switch(dir){
      case 1: // Direita
         if(lab[posL][++posC] == 'b'){
            bonus++;
            lab[posL][posC] = ' ';
         }
         push_pilha(p,eVisitados);
         eVisitados.x = posL;
         eVisitados.y = posC;
         insere_final(list,eVisitados);
         break;
      case 2: // Esquerda
         if(lab[posL][--posC] == 'b'){
            bonus++;
            lab[posL][posC] = ' ';
         }
         push_pilha(p,eVisitados);
         eVisitados.x = posL;
         eVisitados.y = posC;
         insere_final(list,eVisitados);
         break;

      case 3: // Baixo
         if(lab[++posL][posC] == 'b'){
            bonus++;
            lab[posL][posC] = ' ';
         }
         push_pilha(p,eVisitados);
         eVisitados.x = posL;
         eVisitados.y = posC;
         insere_final(list,eVisitados);
         break;

      case 4: // Cima
         if(lab[--posL][posC] == 'b'){
            bonus++;
            lab[posL][posC] = ' ';
         }
         push_pilha(p,eVisitados);
         eVisitados.x = posL;
         eVisitados.y = posC;
         insere_final(list,eVisitados);
         break;

      case 0: // Voltar
         if(pop_pilha(p,&eVisitados)){
            posL = eVisitados.x;
            posC = eVisitados.y;
         }else{
            num = 0; // fim das possibilidades
         }
         break;
      }

      ;
   }while(num);

    termina_lista(list);
    termina_pilha(p);
}

/* 0 - Início inexistente
   1 - Dois ou mais
   2 - OK
*/
int busca_inicio(char **lab,int linha,int coluna, int *posX, int *posY){
   int l,c,achou;
   achou = 0;
   for( l = 0; l < linha ; l++)
      for( c = 0 ; c < coluna ; c++)
         if(lab[l][c] == 's'){
            if(achou){ // Mais de um início possível
               return 1;
            }else{
               *posX = l;
               *posY = c;
               achou = 1;
            }
         }
   if(achou)
      return 2;
   else
      return 0;
}

// Movimenta pelo labirinto para verificar a sua integridade
int verificar_integridade(char **lab,int linha,int coluna){
   int l,c,l2,c2,
      inicio = busca_inicio(lab, linha, coluna, &l, &c);

   if(inicio != 2)
      return 0;

   // Verifica se o início está nas bordas
   if( (c > 0 && c < (coluna - 1) && (l != 0 || l != (linha - 1) ) ) )
      return 0;

   // Primeira linha
   l2 = 0;
   for(c2 = 0 ; c2 < coluna ; c2++)
      if((l2 != l && c2 != c) && lab[l2][c2] != 'x')
         return 0;

   // Ultima linha
   l2 = linha - 1;
   for(c2 = 0 ; c2 < coluna ; c2++)
      if((l2 != l && c2 != c) && lab[l2][c2] != 'x')
         return 0;

   // Primeira coluna
   c2 = 0;
   for(l2 = 0 ; l2 < linha ; l2++)
      if((l2 != l && c2 != c) && lab[l2][c2] != 'x')
         return 0;

   // Ultima coluna
   c2 = coluna -1;
   for(l2 = 0 ; l2 < linha ; l2++)
      if((l2 != l && c2 != c) && lab[l2][c2] != 'x')
         return 0;

   return 1;
}

char menu(){
   char op;
   do{
      printf("\n\n Deseja sair? 1-Sim, 2-Não: ");
      op = _getche();
   }while(op > '2' || op < '1');

   return op;
}

void limpa_tela(){
   system("cls");
}

/*
   Recebe o endereço de memória de uma string como parâmetro,
   remove o char '\n' da string.
*/
void corrige_string(char *str){
   if (str[strlen(str)-1] == '\n')
      str[strlen(str)-1] = '\0';
}
