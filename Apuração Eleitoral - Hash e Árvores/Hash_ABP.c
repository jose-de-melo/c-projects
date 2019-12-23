#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash_ABP.h"

long int numero_colisoes_hash_abp = 0; // Variável global utilizada para contagem de colisões.

apontador cria_abp(){
    return NULL;
}

/* Insere um elemento (cédula) na ABP. A inserção não admite chaves duplicadas.
* Retorna 1 em caso de sucesso ou 0, em caso de falha.
*/
int insere_abp(apontador *p, tipo_cedula e){
    if(*p == NULL){
        *p = (apontador)malloc(sizeof(tipo_nodo_abp));
        if(*p){
            (*p)->cedula = e;
            (*p)->esq = NULL;
            (*p)->dir = NULL;
            return 1;
        }
        else
            return 0;
    }
    else{
        if(strcmp((*p)->cedula.tituloEleitor, e.tituloEleitor) < 0)
            return insere_abp(&(*p)->dir, e);
        else
            if(strcmp((*p)->cedula.tituloEleitor, e.tituloEleitor) > 0)
                return insere_abp(&(*p)->esq, e);
            else
                return 0;
    }
}

int pesquisa_abp(apontador p, tipo_chave ch, tipo_cedula *e){
    if(p == NULL)
        return 0;
    else
        if(strcmp(p->cedula.tituloEleitor, ch) < 0)
            return pesquisa_abp(p->dir, ch, e);
        else
            if(strcmp(p->cedula.tituloEleitor, ch) > 0)
                return pesquisa_abp(p->esq, ch, e);
            else{
                *e = p->cedula;
                return 1;
            }
}

int remove_abp(apontador *p, tipo_chave ch, tipo_cedula *e){
    apontador aux;

    if(*p == NULL)
        return 0;
    else
        if(strcmp((*p)->cedula.tituloEleitor, ch) < 0)
            return remove_abp(&(*p)->dir, ch, e);
        else
            if(strcmp((*p)->cedula.tituloEleitor, ch) > 0)
                return remove_abp(&(*p)->esq, ch, e);
            else{
                *e = (*p)->cedula;
                aux = *p;
                if((*p)->esq == NULL)
                    *p = (*p)->dir;
                else
                    if((*p)->dir == NULL)
                        *p = (*p)->esq;
                    else{
                        p = &(*p)->esq;
                        while((*p)->dir != NULL)
                            p = &(*p)->dir;
                        aux->cedula = (*p)->cedula;
                        aux = *p;
                        *p = (*p)->esq;
                    }
                free(aux);
                return 1;
            }
}// remove_abp()

/** Altera uma cédula de eleitor presente na árvore binária de pesquisa. A chave a ser alterada é especificado
* através do parâmetro tipo_cedula e.
*
* Retorna 1 em caso de alteração realizada ou 0, em caso de falha.
*/
int altera_abp(apontador *p, tipo_cedula e){
    // Só é possível registrar um voto por vez! E não é permitido registrar cédula sem voto.
    if((e.votoPresidente && e.votoSenador) || (!e.votoPresidente && !e.votoSenador))
        return 0;

    if(*p == NULL){ // Em caso de não encontrar a chave especificada, realiza a inserção!
        *p = (apontador)malloc(sizeof(tipo_nodo_abp));
        if(*p){
            (*p)->cedula = e;
            (*p)->esq = NULL;
            (*p)->dir = NULL;
            return 1;
        }
        else
            return 0;
    }
    else
        if(strcmp((*p)->cedula.tituloEleitor, e.tituloEleitor) < 0)
            return altera_abp(&(*p)->dir, e);
        else
            if(strcmp((*p)->cedula.tituloEleitor, e.tituloEleitor) > 0)
                return altera_abp(&(*p)->esq, e);
            else
                // Verifica se o voto já foi registrado para o candidato escolhido.
                if(((*p)->cedula.votoPresidente && e.votoPresidente) || ((*p)->cedula.votoSenador && e.votoSenador))
                    return 0;
                else{
                    if(e.votoPresidente)
                        (*p)->cedula.votoPresidente = e.votoPresidente;
                    else
                        (*p)->cedula.votoSenador = e.votoSenador;
                    return 1;
                }
}

void termina_abp(apontador p){
    if(p != NULL){
        termina_abp(p->esq);
        termina_abp(p->dir);
        free(p);
    }
}

/* Percorrendo a árvore in-ordem (ESQ - PAI - DIR). */
void imprime_abp(apontador p){
    if(p != NULL){
        imprime_abp(p->esq);
        printf("%s, ", p->cedula.tituloEleitor);
        imprime_abp(p->dir);
    }
}

/* Aloca espaço em memória para uma tabela hash com resolução de colisões por árvore binária de pesquisa
* (tabela de cédulas de eleitores), e com o tamanho passado como parâmetro. Inicializa todas as posições
* da tabela com um apontador para uma ABP.
*
* Retorna a tabela alocada ou NULL em caso de falha.
*/
tabela_hash_abp cria_tabela_hash_abp(long int tamanho){
    tabela_hash_abp t = NULL;
    int i;

    t = (tabela_hash_abp) malloc(sizeof(tipo_tabela_hash_abp));
    if(t){
        t->elementos = (apontador*) malloc(sizeof(apontador) * tamanho);
        if(t->elementos){
            t->tamanho = tamanho;
            for(i = 0; i < tamanho; i++)
                t->elementos[i] = cria_abp();
        }
        else{
            free(t);
            t = NULL;
        }
    }
    return t;
}

/* Libera o espaço em memória reservado para uma tabela hash com árvore binária de pesquisa.
*/
void termina_tabela_hash_abp(tabela_hash_abp t){
    int i;

    if(t){
        for(i = 0; i < t->tamanho; i++)
            termina_abp(t->elementos[i]);
        free(t->elementos);
        free(t);
    }
}

int insere_tabela_hash_abp(tabela_hash_abp t, tipo_cedula e){
    int indice = hash1(e.tituloEleitor, t->tamanho);

    return insere_abp(&(t->elementos[indice]), e);
}

int remove_tabela_hash_abp(tabela_hash_abp t, tipo_chave ch, tipo_cedula *e){
    int indice = hash1(ch, t->tamanho);

    return remove_abp(&(t->elementos[indice]), ch, e);
}



int pesquisa_tabela_hash_abp(tabela_hash_abp t, tipo_chave ch, tipo_cedula *e){
    int indice = hash1(ch, t->tamanho);

    return pesquisa_abp(t->elementos[indice], ch, e);
}

int altera_tabela_hash_abp(tabela_hash_abp t, tipo_cedula e){
    int indice = hash1(e.tituloEleitor, t->tamanho);

    if(t->elementos[indice])
        numero_colisoes_hash_abp++; // Conta o número de colisões.
    return altera_abp(&t->elementos[indice], e);
}

long int tamanho_tabela_hash_abp(tabela_hash_abp t){
    return t->tamanho;
}

long int retorna_numero_colisoes_hash_abp(){
    return numero_colisoes_hash_abp;
}


