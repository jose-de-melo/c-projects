#include <stdio.h>
#include <stdlib.h>
#include "Estruturas.h"

lista cria_lista(){
   lista l;
   l = (lista)malloc(sizeof(tipo_lista_visitados));

   if(!l)
      return NULL;

   l->inicio = NULL;
   l->fim = NULL;
   l->tam = 0;

   return l;
}

// Insere um elemento no final da lista
int insere_final(lista l , tipo_elemento_visitados eVisitados){
   tipo_nodo_visitados *nVisitados = (tipo_nodo_visitados*)malloc(sizeof(tipo_nodo_visitados));
    tipo_nodo_visitados *ns;
   if(!nVisitados)
      return 0;

   nVisitados->info = eVisitados;
   nVisitados->prox = NULL;

   // Primero nodo
   if(!l->inicio){
      l->inicio = nVisitados;
   }else{
      l->fim->prox = nVisitados;
   }

   l->fim = nVisitados;
   l->tam++;

   return 1;
}

// Retorna a posição do elemento ou -1 caso não exista
int busca_elemento_lista(lista l, tipo_elemento_visitados eVisitados){
   int c;
   tipo_nodo_visitados *nVisitados;

   nVisitados = l->inicio;
   c = 1;
   while(nVisitados){
      if(nVisitados->info.x == eVisitados.x && nVisitados->info.y == eVisitados.y)
         return c;
      c++;

      nVisitados = nVisitados->prox;
   }

   return -1;
}

void termina_lista(lista f){
    tipo_nodo_visitados *p;
    while(f->inicio){
        p = f->inicio;
        f->inicio = f->inicio->prox;
        free(p);
    }
    free(f);
}

/*****************************************************************************************/
//Pilha

pilha cria_pilha(){
    pilha p = (pilha)malloc(sizeof(tipo_pilha));

    if(p){
        p->tamanho = 0;
        p->topo = NULL;
    }
    return p;
}

int push_pilha(pilha p, tipo_elemento_visitados eVisitados){
    tipo_nodo_pilha *nPilha = (tipo_nodo_pilha*)malloc(sizeof(tipo_nodo_pilha));

    if(!nPilha)
        return -1;
    nPilha->info = eVisitados;
    nPilha->prox = p->topo;
    p->topo = nPilha;
    p->tamanho++;

    return 1;
}

int pop_pilha(pilha p, tipo_elemento_visitados *eVisitados){
    tipo_nodo_pilha *nPilha;

    if(p->tamanho){
        nPilha = p->topo;
        p->topo = p->topo->prox;
        *eVisitados = nPilha->info;
        free(nPilha);
        p->tamanho--;
        return 1;
    }
    return 0;
}

void termina_pilha(pilha p){
    tipo_nodo_pilha *a;
    while(p->topo){
        a=p->topo;
        p->topo = p->topo->prox;
        free(a);
    }
    free(p);
}


