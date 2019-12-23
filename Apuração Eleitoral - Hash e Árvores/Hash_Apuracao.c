#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash_apuracao.h"
#include "Constantes.h"

/*Cria uma tabela hash com resolu��o de colis�o por hashing duplo.
  Retorna uma refer�ncia para a tabela constru�da, ou nulo se houve algum erro.
*/
hash_apuracao criarTHDApuracao(unsigned int m){
    hash_apuracao tabela = (hash_apuracao)malloc(sizeof(tipo_hash_apuracao));
    if(tabela){
        unsigned i;
        tabela->cedula = (cedula_apuracao*) malloc(sizeof(cedula_apuracao) * m);

       /*Inicializando os atributos das c�dulas de apura��o, com numero do candidato = -1 e n�mero de votos = 0.*/
        cedula_apuracao cedula = {-1, 0};
        for(i = 0; i < m; i++){
            tabela->cedula[i] = cedula;
        }

        tabela->M = m;
        tabela->quantidade_dados = 0;

        tabela->campo_controle = (unsigned int*) malloc(sizeof(unsigned int) * m);
        for(i = 0; i < m; i++)
            tabela->campo_controle[i] = 0;

        return tabela;
    }
    return NULL;
}

/*Calcula e retorna a posi��o que a chave deve ocupar na tabela.*/
unsigned int hash_ap(hash_apuracao tabela, int chave){
    return chave % tabela->M;
}

/*Calcula o incremento que ser� usado caso haja colis�es.*/
unsigned int hash_ap2(hash_apuracao tabela, unsigned int chave){
    return tabela->M - 2 - chave % (tabela->M - 2);
}

/*Procura um ponto e realiza a inser��o de uma nova c�dula de apura��o na tabela, com valor de 1 voto.
  Se esta c�dula de apura��o j� existe na tabela, aumenta em uma unidade o n�mero de votos. */
int insere_hash_apuracao(hash_apuracao tabela, int chave, int listaCandidatos[], int *qtd_votos){
    unsigned int posicao, i = 1, incremento;

    /*A vari�vel posicao recebe a posi��o de inser��o.*/
    posicao = hash_ap(tabela, chave);

    /*A vari�vel incremento recebe o valor do incremento de posi��es que ser� usado caso haja colis�es.*/
    incremento = hash_ap2(tabela, posicao);

    while(i <= tabela->M && tabela->campo_controle[posicao] == 1){
        if(tabela->cedula[posicao].numCandidato == chave){
           *qtd_votos = ++tabela->cedula[posicao].numVotos;
           return 1;
        }
        posicao = (posicao + incremento) % tabela->M;
        i++;
    }

    if(i > tabela->M)  return 0;

    /*Insere uma nova cedula de apuracao com valor de 1 voto.*/
    cedula_apuracao cedula = {chave,1};
    tabela->cedula[posicao] = cedula;
    listaCandidatos[tabela->quantidade_dados] = tabela->cedula[posicao].numCandidato;
    tabela->quantidade_dados++;
    tabela->campo_controle[posicao] = OCUPADO;
    return 1;
}

/*Pesquisa um elemento na tabela pela sua chave, caso encontre, retorna o valor encontrado em *cedula.
  retorna 1 se o elemento foi encontrado, 0 se n�o.*/
int pesquisa_hash_apuracao(hash_apuracao tabela, int chave , cedula_apuracao *cedula){
    int posicao,j = 1;

    if(tabela->quantidade_dados == 0) return -1;

    posicao = hash_ap(tabela,chave);
    if(tabela->cedula[posicao].numCandidato == chave && tabela->campo_controle[posicao] == OCUPADO){
        (*cedula) = tabela->cedula[posicao];
        return posicao;
    }

    unsigned incremento = hash_ap2(tabela, posicao);

    do{
        posicao = (posicao+incremento) % tabela->M;

        if(tabela->campo_controle[posicao] == OCUPADO){
            if(tabela->cedula[posicao].numCandidato == chave){
                (*cedula) = tabela->cedula[posicao];
                return posicao;
            }
        }else{
            if(tabela->campo_controle[posicao] == VAZIO)
                return -1;
        }
        j++;
    }while(j < tabela->M);

    return -1;
}

/*Remove um item da tabela com a chave indicada e retorna uma c�pia deste item em *cedula.
  Retorna 1 se o item foi removido, 0 se n�o.*/
int remove_hash_apuracao(hash_apuracao tabela, int chave, cedula_apuracao *cedula){
    if(tabela->quantidade_dados == 0) return 0;
    cedula_apuracao cedulaAux;
    int posicao  = pesquisa_hash_apuracao(tabela, chave, &cedulaAux);

    if(posicao == -1) return 0;

    (*cedula) = cedulaAux;

    if(tabela->cedula[posicao].numVotos > 1){
        tabela->cedula[posicao].numVotos--;
    }
    else{
        cedula_apuracao cedulaVazia = {-1, VAZIO};
        tabela->cedula[posicao] = cedulaVazia;
        tabela->campo_controle[posicao] = REMOVIDO;
        tabela->quantidade_dados--;
    }

    return 1;
}

void termina_hash_apuracao(hash_apuracao tabela){
    free(tabela->cedula);
    free(tabela);
}
