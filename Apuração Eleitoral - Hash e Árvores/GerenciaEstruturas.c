#include "GerenciaEstruturas.h"
#include "stdlib.h"

void* criaEstrutura(long int m, int tipoEstrutura){
    switch(tipoEstrutura){
        case 1: return (void*)cria_tabela_dupla(m);
        case 2: return (void*)cria_abp(m);
        case 3: return (void*)cria_arvore_avl(m);
        default: return NULL;
    }
}

int inserirItemEstrutura(void *estr,tipo_cedula cedula,int tipoTabela){
	switch(tipoTabela){
        case 1:return insere_tabela_dupla((tabela_dupla)estr, cedula);
        case 2:return insere_abp((apontador*)&estr,cedula);
        case 3:return insere_arvore_avl((tabela_avl*)&estr,cedula);
        default: return 0;
    }
}

int pesquisarItemEstrutura(void *estr,tipo_chave chave,tipo_cedula *procurar,int tipoTabela){
    switch(tipoTabela){
        case 1: return pesquisa_tabela_dupla((tabela_dupla)estr, chave);
        case 2: return pesquisa_abp((apontador)estr,chave, procurar);
        case 3: return consulta_arvore_avl((tabela_avl)estr, chave, &(*procurar));
        default: return 0;
    }
}

int removerItemEstrutura(void *estr,tipo_chave chave, tipo_cedula *procurar,int tipoTabela){
    switch(tipoTabela){
        case 1: return remove_tabela_dupla((tabela_dupla)estr , chave , &(*procurar));
        case 2: return remove_abp((apontador*)&estr, chave, procurar);
        case 3: return remove_arvore_avl((tabela_avl*)estr,chave);
        default: return 0;
    }
}

void terminarEstrutura(void *estr,int tipoTabela){
   switch(tipoTabela){
        case 1: termina_tabela_dupla((tabela_dupla)estr); break;
        case 2: termina_abp((apontador)estr); break;
        case 3: libera_arvore_avl((tabela_avl)estr); break;
    }
}
