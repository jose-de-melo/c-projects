#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ListaEncadeada.h"

lista cria_lista(){
    lista l;

    l = (lista)malloc(sizeof(tipo_lista));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho = 0;
    }
    return l;
}

int insere_apos(lista l, tipo_elemento_lista e){
    tipo_nodo_lista *p;

    p = (tipo_nodo_lista*)malloc(sizeof(tipo_nodo_lista));

    if(!p)
        return 0;

    p->info = e;
    p->next = NULL;

    /* Verificando se a lista está vazia. */
    if(l->first == NULL)
        l->first = p;
    else
        l->last->next = p;

    l->last = p;
    l->tamanho++;

    return 1;
}

void termina_lista(lista l){
    tipo_nodo_lista *p;

    if(l){
        while(l->first != NULL){
            p = l->first;
            l->first = l->first->next;
            free(p);
        }
        free(l);
    }
}

int get_elemento(lista l, tipo_elemento_lista *e, int indice){
    int i;
    tipo_nodo_lista *p;

    if(indice < 1 || indice > l->tamanho)
        return 0;

    p = l->first;
    for(i = 1; i < indice; i++)
        p = p->next;
    *e = p->info;
    return 1;
}

int tamanho_lista(lista l){
    return l->tamanho;
}

int lista_cheia(lista l){
    tipo_nodo_lista *p;

    p = (tipo_nodo_lista*)malloc(sizeof(tipo_nodo_lista));
    if(!p)
        return 1;
    else{
        free(p);
        return 0;
    }
}

int busca_elemento(lista l, tipo_chave ch, tipo_elemento_lista *e){
    tipo_nodo_lista *p;

    p = l->first;
    while(p != NULL){
        if(strcmp(p->info.chave, ch) == 0){
            *e = p->info;
            return 1;
        }
        else
            p = p->next;
    }

    return 0;
}

int pesquisa_elemento(lista l, tipo_chave ch) {
    tipo_nodo_lista *p;
    int pos = 1;

    p = l->first;
    while(p != NULL){
        if(strcmp(p->info.chave, ch) == 0){
            return pos;
        }
        else{
            p = p->next;
            pos++;
        }
    }
    return 0;
}

int atualiza_elemento(lista l, tipo_elemento_lista e, tipo_chave ch){
    tipo_nodo_lista *p;

    p = l->first;
    while(p != NULL){
        if(strcmp(p->info.chave, ch) == 0){
            p->info = e;
            return 1;
        }
        else
            p = p->next;
    }

    return 0;
}

int insere_inicio(lista l, tipo_elemento_lista e){
    tipo_nodo_lista *p;

    p = (tipo_nodo_lista*)malloc(sizeof(tipo_nodo_lista));
    if(!p)
        return 0;
    else{
        p->info = e;
        p->next = l->first;
        l->tamanho++;
        l->first = p;
        if(l->tamanho == 1)
            l->last = p;
        return 1;
    }
}

int insere_posicao(lista l, tipo_elemento_lista e, int indice){
    int i;
    tipo_nodo_lista *p, *a;

    /* Verificando se é uma posição válida */
    if(indice < 1 || indice > (l->tamanho + 1))
        return 0;
    else{
        if(indice == 1)
            return insere_inicio(l, e);
        else
            if(indice == (l->tamanho + 1))
                return insere_apos(l, e);
            else{
                p = (tipo_nodo_lista*)malloc(sizeof(tipo_nodo_lista));
                if(p){
                    p->info = e;
                    a = l->first;
                    for(i = 1; i < (indice - 1); i++)
                        a = a->next;
                    p->next = a->next;
                    a->next = p;
                    return 1;
                }
                else
                    return 0;
            }
    }
}

int insere_lista_ordenada(lista l, tipo_elemento_lista e){
    tipo_nodo_lista *p;
    int pos = 1;

    p = l->first;
    while(p != NULL){
        if(strcmp(p->info.chave, e.chave) < 0){
            p = p->next;
            pos++;
        }
        else
            break;
    }
    return insere_posicao(l, e, pos);
}

int remove_elemento(lista l, int indice){
    int i;
    tipo_nodo_lista *p, *a;

    /* Verificando se é uma posição válida */
    if(indice < 1 || indice > l->tamanho)
        return 0;
    else{
        p = l->first;
        for(i = 1; i < indice; i++){
            a = p;
            p = p->next;
        }
        if(l->first == p)
            l->first = p->next;
        else
            if(l->last == p){
                l->last = a;
                a->next = NULL;
            }
            else
                a->next = p->next;
        free(p);
        l->tamanho--;
        return 1;
    }
}
