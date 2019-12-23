#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash_AVL.h"


tabela_avl* cria_arvore_avl(){
    tabela_avl* raiz = (tabela_avl*) malloc(sizeof(nodo_avl));

    if(raiz != NULL)
        *raiz = NULL;

    return raiz;
}

void libera_nodo_avl(struct nodo_avl* nodo_avl){
    if(nodo_avl == NULL)
        return;
    libera_nodo_avl(nodo_avl->esq);
    libera_nodo_avl(nodo_avl->dir);
    free(nodo_avl);
    nodo_avl = NULL;
}

void libera_arvore_avl(tabela_avl* raiz){
    if(raiz == NULL)
        return;
    libera_nodo_avl(*raiz);
    free(raiz);
}

int altura_nodo_avl(struct nodo_avl* nodo_avl){
    if(nodo_avl == NULL)
        return -1;
    else
    return nodo_avl->altura;
}

int fatorBalanceamento_nodo_avl(tabela_avl* nodo_avl){
    return labs(altura_nodo_avl(nodo_avl->esq) - altura_nodo_avl(nodo_avl->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_arvore_avl(tabela_avl *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int total_nodo_avl_arvore_avl(tabela_avl *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = total_nodo_avl_arvore_avl(&((*raiz)->esq));
    int alt_dir = total_nodo_avl_arvore_avl(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_arvore_avl(tabela_avl *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;

    int alt_esq = altura_arvore_avl(&((*raiz)->esq));
    int alt_dir = altura_arvore_avl(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_arvore_avl(tabela_avl *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("Titulo :: %s\n", (*raiz)->cedula.tituloEleitor);
        preOrdem_arvore_avl(&((*raiz)->esq));
        preOrdem_arvore_avl(&((*raiz)->dir));
    }
}

void emOrdem_arvore_avl(tabela_avl *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_arvore_avl(&((*raiz)->esq));
        printf("Titulo: %s\n", (*raiz)->cedula.tituloEleitor);
        emOrdem_arvore_avl(&((*raiz)->dir));
    }
}

void posOrdem_arvore_avl(tabela_avl *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_arvore_avl(&((*raiz)->esq));
        posOrdem_arvore_avl(&((*raiz)->dir));
        printf("Titulo: %s\n", (*raiz)->cedula.tituloEleitor);
    }
}

int consulta_arvore_avl(tabela_avl raiz, tipo_chave chave, tipo_cedula *cedula){
    if(raiz == NULL)
        return 0; e.

    if(strcmp(raiz->cedula.tituloEleitor, chave) < 0)
        consulta_arvore_avl(raiz->dir, chave, cedula);
    else
        if(strcmp(raiz->cedula.tituloEleitor, chave) > 0)
            consulta_arvore_avl(raiz->esq, chave, cedula);
        else{
            *cedula = raiz->cedula;
            return 1; // Encontrou a chave.
        }
    return 0; // Nao enconcontrou a chave
}

void RotacaoLL(tabela_avl *A){
    struct nodo_avl *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_nodo_avl((*A)->esq),altura_nodo_avl((*A)->dir)) + 1;
    B->altura = maior(altura_nodo_avl(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(tabela_avl *A){
    struct nodo_avl *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_nodo_avl((*A)->esq),altura_nodo_avl((*A)->dir)) + 1;
    B->altura = maior(altura_nodo_avl(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(tabela_avl *A){
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(tabela_avl *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_arvore_avl(tabela_avl *raiz, tipo_cedula cedula){
    int res = 0;

    if((cedula.votoPresidente && cedula.votoSenador) || (!cedula.votoPresidente && !cedula.votoSenador))
        return 0;

    if(*raiz == NULL){//árvore vazia ou nó folha
        struct nodo_avl *nodo;
        nodo = (struct nodo_avl*)malloc(sizeof(struct nodo_avl));
        if(nodo == NULL)
            return 0;

        nodo->cedula = cedula;
        nodo->altura = 0;
        nodo->esq = NULL;
        nodo->dir = NULL;
        *raiz = nodo;
        return 1;
    }

    struct nodo_avl *atual = *raiz
    if(strcmp(cedula.tituloEleitor, atual->cedula.tituloEleitor) < 0 ){
        if((res = insere_arvore_avl(&(atual->esq), cedula)) == 1){
            if(fatorBalanceamento_nodo_avl(atual) >= 2){
                if(strcmp(cedula.tituloEleitor, (*raiz)->cedula.tituloEleitor) < 0){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(strcmp(cedula.tituloEleitor, atual->cedula.tituloEleitor) > 0 ){
           if((res = insere_arvore_avl(&(atual->dir), cedula)) == 1){
                if(fatorBalanceamento_nodo_avl(atual) >= 2){
                    if(strcmp((*raiz)->cedula.tituloEleitor, cedula.tituloEleitor, ) < 0){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            if(((*raiz)->cedula.votoPresidente && cedula.votoPresidente) || ((*raiz)->cedula.votoSenador && cedula.votoSenador))
                return 0;
            else{
                if(cedula.votoPresidente)
                    (*raiz)->cedula.votoPresidente = cedula.votoPresidente;
                else
                    (*raiz)->cedula.votoSenador = cedula.votoSenador;

                return 1;
            }
        }
    }

    atual->altura = maior(altura_nodo_avl(atual->esq), altura_nodo_avl(atual->dir)) + 1;

    return res;
}

struct nodo_avl* procuraMenodo_avlr(struct nodo_avl* atual){
    struct nodo_avl *nodo_avl1 = atual;
    struct nodo_avl *nodo_avl2 = atual->esq;
    while(nodo_avl2 != NULL){
        nodo_avl1 = nodo_avl2;
        nodo_avl2 = nodo_avl2->esq;
    }
    return nodo_avl1;
}

int remove_arvore_avl(tabela_avl *raiz, tipo_chave chave){
	if(*raiz == NULL){
	    return 0;
	}

    int res;
	if(strcmp(chave, (*raiz)->cedula.tituloEleitor) > 0 ){
	    if((res = remove_arvore_avl(&(*raiz)->esq, chave)) == 1){
            if(fatorBalanceamento_nodo_avl(*raiz) >= 2){
                if(altura_nodo_avl((*raiz)->dir->esq) <= altura_nodo_avl((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}else
        if(strcmp((*raiz)->cedula.tituloEleitor, chave) < 0 ){
            if((res = remove_arvore_avl(&(*raiz)->dir, chave)) == 1){
                if(fatorBalanceamento_nodo_avl(*raiz) >= 2){
                    if(altura_nodo_avl((*raiz)->esq->dir) <= altura_nodo_avl((*raiz)->esq->esq) )
                        RotacaoLL(raiz);
                    else
                        RotacaoLR(raiz);
                }
            }
        }else{
            if(strcmp( chave, (*raiz)->cedula.tituloEleitor) == 0){
                if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
                    struct nodo_avl *aux = (*raiz);
                    if((*raiz)->esq != NULL)
                        *raiz = (*raiz)->esq;
                    else
                        *raiz = (*raiz)->dir;
                    free(aux);
                }else { 
                    struct nodo_avl* temp = procuraMenodo_avlr((*raiz)->dir);
                    (*raiz)->cedula = temp->cedula;
                    remove_arvore_avl(&(*raiz)->dir, (*raiz)->cedula.tituloEleitor);

                    if(fatorBalanceamento_nodo_avl(*raiz) >= 2){
                        if(altura_nodo_avl((*raiz)->esq->dir) <= altura_nodo_avl((*raiz)->esq->esq))
                            RotacaoLL(raiz);
                        else
                            RotacaoLR(raiz);
                    }
                }
                if (*raiz != NULL)
                    (*raiz)->altura = maior(altura_nodo_avl((*raiz)->esq),altura_nodo_avl((*raiz)->dir)) + 1;
                return 1;
            }
        }

	(*raiz)->altura = maior(altura_nodo_avl((*raiz)->esq),altura_nodo_avl((*raiz)->dir)) + 1;

	return res;
}
