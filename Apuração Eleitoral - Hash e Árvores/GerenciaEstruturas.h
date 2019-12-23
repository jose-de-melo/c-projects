#ifndef GERENCIAESTRUTURAS_H_INCLUDED
#define GERENCIAESTRUTURAS_H_INCLUDED

#include "Hash_Duplo.h"
#include "Hash_AVL.h"
#include "Hash_ABP.h"
#include "CedulaEleitoral.h"

void* criaEstrutura(long int m,int tipoTabela);
int inserirItemEstrutura(void *estr,tipo_cedula cedula,int tipoTabela);
int pesquisarItemEstrutura(void *estr,tipo_chave chave,tipo_cedula *procurar,int tipoTabela);
int removerItemEstrutura(void *estr,tipo_chave chave,tipo_cedula *procurar,int tipoTabela);
void terminarEstrutura(void *estr,int tipoTabela);

#endif /* GERENCIAESTRUTURAS_H_INCLUDED*/
