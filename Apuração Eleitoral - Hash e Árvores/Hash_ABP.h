#ifndef HASH_ABP_H_INCLUDED
#define HASH_ABP_H_INCLUDED

#include "CedulaEleitoral.h"

typedef struct nodo_abp{
    tipo_cedula cedula;
    struct nodo_abp *esq, *dir;

}tipo_nodo_abp;

typedef tipo_nodo_abp *apontador;

typedef struct{
    apontador *elementos;
    long int tamanho;

}tipo_tabela_hash_abp;

typedef tipo_tabela_hash_abp *tabela_hash_abp;

apontador cria_abp();
int insere_abp(apontador*, tipo_cedula);
int pesquisa_abp(apontador, tipo_chave, tipo_cedula*);
int remove_abp(apontador*, tipo_chave, tipo_cedula*);
int altera_abp(apontador*, tipo_cedula);
void termina_abp(apontador);
void imprime_abp(apontador);

tabela_hash_abp cria_tabela_hash_abp(long int);
void termina_tabela_hash_abp(tabela_hash_abp);
int insere_tabela_hash_abp(tabela_hash_abp, tipo_cedula);
int remove_tabela_hash_abp(tabela_hash_abp, tipo_chave, tipo_cedula*);
int pesquisa_tabela_hash_abp(tabela_hash_abp, tipo_chave, tipo_cedula*);
int altera_tabela_hash_abp(tabela_hash_abp, tipo_cedula);
long int tamanho_tabela_hash_abp(tabela_hash_abp);
long int retorna_numero_colisoes_hash_abp();
long int hash1(tipo_chave, long int);

#endif // HASH_ABP_H_INCLUDED
