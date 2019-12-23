#ifndef HASH_AVL_H_INCLUDED
#define HASH_AVL_H_INCLUDED


#include "CedulaEleitoral.h"

typedef struct nodo_avl{
    tipo_cedula cedula;
    struct nodo_avl *esq, *dir;
    int altura;
}nodo_avl;

typedef nodo_avl *tabela_avl;

tabela_avl* cria_arvore_avl();
void libera_arvore_avl(tabela_avl *raaiz);

int insere_arvore_avl(tabela_avl *raiz, tipo_cedula);
int remove_arvore_avl(tabela_avl *raiz, tipo_chave);
int esta_vazia_arvore_avl(tabela_avl *raiz);
int altura_arvore_avl(tabela_avl *raiz);
int total_nodo_avl(tabela_avl *raiz);
int consulta_arvore_avl(tabela_avl, tipo_chave, tipo_cedula*);

void preOrdem_arvore_avl(tabela_avl *raiz);
void emOrdem_arvore_avl(tabela_avl *raiz;
void posOrdem_arvore_avl(tabela_avl *raiz);

void RotacaoRR(tabela_avl*);
void RotacaoLL(tabela_avl*);
void RotacaoLR(tabela_avl*);
void RotacaoRL(tabela_avl*);

#endif // HASH_AVL_H_INCLUDED
