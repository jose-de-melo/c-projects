#ifndef HASH_APURACAO_H_INCLUDED
#define HASH_APURACAO_H_INCLUDED

typedef struct{
    int numCandidato,
        numVotos;
}cedula_apuracao;

typedef struct{
    cedula_apuracao *cedula;
    unsigned int M, /* Tamanho da tabela*/
        quantidade_dados, /*Quantidade de dados da tabela*/
        *campo_controle;
}tipo_hash_apuracao;

typedef tipo_hash_apuracao *hash_apuracao;

hash_apuracao criarTHDApuracao(unsigned int);
int insere_hash_apuracao(hash_apuracao, int, int listaCandidatos[], int*);
int pesquisa_hash_apuracao(hash_apuracao, int, cedula_apuracao*);
int remove_hash_apuracao(hash_apuracao, int, cedula_apuracao*);
void termina_hash_apuracao(hash_apuracao);

#endif /* HASH_APURACAO_H_INCLUDED*/
