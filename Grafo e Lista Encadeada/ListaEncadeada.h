#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

#include "Estruturas.h"

typedef struct{
    tipo_chave chave;
    tipo_peso peso;
}tipo_elemento_lista;

typedef struct nodo_lista{
    tipo_elemento_lista info;
    struct nodo_lista *next;
}tipo_nodo_lista;

typedef struct{
    tipo_nodo_lista *first, *last;
    int tamanho;
}tipo_lista;

typedef tipo_lista* lista;

lista cria_lista();
int insere_apos(lista, tipo_elemento_lista);
void termina_lista(lista);
int get_elemento(lista, tipo_elemento_lista*, int);
int tamanho_lista(lista);
int lista_cheia(lista l);
int busca_elemento(lista, tipo_chave, tipo_elemento_lista*);
int pesquisa_elemento(lista, tipo_chave);
int atualiza_elemento(lista, tipo_elemento_lista, tipo_chave);
int insere_inicio(lista, tipo_elemento_lista);
int insere_posicao(lista, tipo_elemento_lista, int);
int insere_lista_ordenada(lista, tipo_elemento_lista);
int remove_elemento(lista, int);




#endif // LISTAENCADEADA_H_INCLUDED
