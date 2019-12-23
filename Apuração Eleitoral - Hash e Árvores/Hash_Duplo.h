#ifndef HASHDUPLO_H_INCLUDED
#define HASHDUPLO_H_INCLUDED

#include "CedulaEleitoral.h"
#define STRING_DELETADA "DELETADA"
#define STRING_VAZIA ""

typedef struct{
    tipo_cedula *elementos;
    long int tamanho;
}tipo_tabela_dupla;

typedef tipo_tabela_dupla *tabela_dupla;

tabela_dupla cria_tabela_dupla(long int);
void termina_tabela_dupla(tabela_dupla);
int insere_tabela_dupla(tabela_dupla, tipo_cedula);
int remove_tabela_dupla(tabela_dupla, tipo_chave, tipo_cedula*);
long int pesquisa_tabela_dupla(tabela_dupla, tipo_chave);
int altera_tabela_dupla(tabela_dupla, tipo_cedula);
long int tamanho_tabela_dupla(tabela_dupla);
long int retorna_numero_colisoes_hash_duplo();

#endif // HASHDUPLO_H_INCLUDED
