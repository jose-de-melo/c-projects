#include <stdlib.h>
#include <string.h>

#include "Hash.h"

long int hash1(tipo_chave ch, long int tamanho){
    int i;
    long int soma = ch[0];

    for(i = 1; ch[i] != '\0'; i++)
        soma = (soma * 251 + ch[i]) % tamanho;


    return soma;
}

long int hash2(tipo_chave ch, long int tamanho){
    long int tamanho_tabela_hash2 = tamanho - 1, soma = ch[0];
    int i;

    if(tamanho_tabela_hash2 != 0){
        for(i = 1; ch[i] != '\0'; i++)
            soma = (soma * 251 + ch[i]) % tamanho_tabela_hash2;
        return (1 + abs(soma));
    }
    else
        return 1;
}

