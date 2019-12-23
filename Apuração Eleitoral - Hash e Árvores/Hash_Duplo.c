#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Hash_Duplo.h"
#include "Hash.h"


long int numero_colisoes_hash_duplo = 0; // Variável global utilizada para contagem de colisões do Hash Duplo.

tabela_dupla cria_tabela_dupla(long int tamanho){
    tabela_dupla t = NULL;
    long int i;
    tipo_cedula cedula;



    t = (tabela_dupla) malloc(sizeof(tipo_tabela_dupla));
    if(t){
        t->elementos = (tipo_cedula*) malloc(sizeof(tipo_cedula) * tamanho);
        if(t->elementos){
            t->tamanho = tamanho;
            strcpy(cedula.tituloEleitor, STRING_VAZIA);
            cedula.votoPresidente = VAZIO;
            cedula.votoSenador = VAZIO;

            for(i = 0; i < tamanho; i++)
                t->elementos[i] = cedula;
        }
        else{
            free(t);
            t = NULL;
        }
    }

    return t;
}

void termina_tabela_dupla(tabela_dupla t){
    if(t){
        free(t->elementos);
        free(t);
    }
}

int insere_tabela_dupla(tabela_dupla t, tipo_cedula e){
    long int indice, k, count;

    if(pesquisa_tabela_dupla(t, e.tituloEleitor) != -1){
        indice = hash1(e.tituloEleitor, t->tamanho);
        k = hash2(e.tituloEleitor, t->tamanho); // A função de hash duplo será o incremento realizado ao índice a cada colisão detectada!
        count = 0;
        while(count < t->tamanho){
            if((strcmp(t->elementos[indice].tituloEleitor, STRING_DELETADA) != 0) && (strcmp(t->elementos[indice].tituloEleitor, STRING_VAZIA) != 0)){
                count++;
                indice = (indice + k) % t->tamanho;
                numero_colisoes_hash_duplo++;
            }
            else
                break;
        }
        if(count != t->tamanho){ // A tabela ainda não está cheia!
            t->elementos[indice] = e;
            return 1;
        }
    }
    return 0;
}

int remove_tabela_dupla(tabela_dupla t, tipo_chave ch, tipo_cedula *e){
    long int indice = pesquisa_tabela_dupla(t, ch);

    if(indice != -1){
        *e = t->elementos[indice];
        strcpy(t->elementos[indice].tituloEleitor, STRING_DELETADA);
        t->elementos[indice].votoPresidente = 0;
        t->elementos[indice].votoSenador = 0;
        return 1;
    }
    else
        return 0;
}


long int pesquisa_tabela_dupla(tabela_dupla t, tipo_chave ch){
    long int indice = hash1(ch, t->tamanho), count, k;

    count = 0;
    k = hash2(ch, t->tamanho); // A função de hash duplo será o incremento realizado ao índice a cada colisão detectada!
    while(count < t->tamanho){
        if(strcmp(t->elementos[indice].tituloEleitor, ch) != 0){
            if(strcmp(t->elementos[indice].tituloEleitor, STRING_VAZIA) != 0){
                count++;
                indice = (indice + k) % t->tamanho;
            }
            else
                return indice;
        }
        else
            return -1;
    }
    return -1;
}

int altera_tabela_dupla(tabela_dupla t, tipo_cedula e){
    long int indice;

    if((e.votoPresidente && e.votoSenador) || (!e.votoPresidente && !e.votoSenador)) // Só é possível registrar um voto por vez! E não é permitido registrar cédula sem voto.
        return 0;

    indice = pesquisa_tabela_dupla(t, e.tituloEleitor);
    if(indice != -1){
        if((t->elementos[indice].votoPresidente && e.votoPresidente) || (t->elementos[indice].votoSenador && e.votoSenador)) // Verifica se o voto já foi registrado para o candidato escolhido.
            return 0;
        else{
            if(e.votoPresidente)
                t->elementos[indice].votoPresidente = e.votoPresidente;
            else
                t->elementos[indice].votoSenador = e.votoSenador;
            return 1;
        }
    }
    else
        return insere_tabela_dupla(t, e); // Em caso de não encontrar a chave especificada, realiza a inserção!
}

long int tamanho_tabela_dupla(tabela_dupla t){
    return t->tamanho;
}

long int retorna_numero_colisoes_hash_duplo(){
    return numero_colisoes_hash_duplo;
}
