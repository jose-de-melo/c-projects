#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED



typedef char tipo_chave[60];

typedef unsigned int tipo_peso;

typedef struct{
    tipo_chave chave;
}tipo_elemento;

typedef struct{
    tipo_chave ch1, ch2;
    tipo_peso prioridade;
}tipo_elemento_fp;

typedef struct nodo{
    tipo_elemento info;
    struct nodo *proximo;
}tipo_nodo;

#endif // ESTRUTURAS_H_INCLUDED
