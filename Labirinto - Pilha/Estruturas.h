#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

// Estrutura da lista
typedef struct{
   int x,y;
}tipo_elemento_visitados;

typedef struct tipo_visitados{
   tipo_elemento_visitados info;
   struct tipo_visitados *prox;
}tipo_nodo_visitados;

typedef struct {
   tipo_nodo_visitados *inicio, *fim;
   int tam;
}tipo_lista_visitados;

typedef tipo_lista_visitados *lista;

lista cria_lista();
void termina_lista(lista f);
int insere_final(lista l , tipo_elemento_visitados eVisitados);
int busca_elemento_lista(lista l, tipo_elemento_visitados eVisitados);

// Fim da estrutura da lista

// Estrutura da pilha
typedef struct nodo_pilha{
   tipo_elemento_visitados info;
   struct nodo_pilha *prox;
}tipo_nodo_pilha;

typedef struct {
   tipo_nodo_pilha *topo;
   int tamanho;
} tipo_pilha;

typedef tipo_pilha *pilha;

pilha cria_pilha();
void termina_pilha(pilha p);
int push_pilha(pilha p, tipo_elemento_visitados eVisitados);
int pop_pilha(pilha, tipo_elemento_visitados *eVisitados);

// Fim da estrutura da pilha

#endif // ESTRUTURAS_H_INCLUDED
