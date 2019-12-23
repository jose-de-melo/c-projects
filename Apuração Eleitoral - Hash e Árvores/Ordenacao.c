#include <stdio.h>
#include <stdlib.h>
#include "Ordenacao.h"

/* Organiza em ordem crescente do número de votos de cada candidato.
   principal = Tabela hash com os elementos.
   listaCandidatos = lista de todos os candidatos que já foram votados.
   apuracao[] = vetor onde a lista ordenada será retornada.
   n = quantidade de dados na tabela principal.
   tamRank = representa a quantidade de dados a serem retornados em apuracao[].
*/
void selectSort(hash_apuracao principal, int listaCandidatos[], cedula_apuracao apuracao[], int n, int tamRank){
	int i, j, posicao_maior;
	int intAux;

	cedula_apuracao *aux = malloc(sizeof(cedula_apuracao));
	cedula_apuracao *aux2 = malloc(sizeof(cedula_apuracao));

	/*Verifica se existe apenas 1 valor*/
	if(n == 1){
		pesquisa_hash_apuracao(principal, listaCandidatos[0], &apuracao[0]);
		return;
	}

	for (i = 0; i < tamRank; i++){
		posicao_maior = i;

		for (j = i + 1 ; j < n; j++){
			pesquisa_hash_apuracao(principal, listaCandidatos[j], aux);
			pesquisa_hash_apuracao(principal, listaCandidatos[posicao_maior], aux2);

			if(aux->numVotos > aux2->numVotos)
				posicao_maior = j;

			/*Se os votos forem iguais, compara o o numero do candidato*/
			else if(aux->numVotos == aux2->numVotos)
				if(aux->numCandidato < aux2->numCandidato)
					posicao_maior = j;
		}

		intAux = listaCandidatos[posicao_maior];
		listaCandidatos[posicao_maior] = listaCandidatos[i];
		listaCandidatos[i] = intAux;
		pesquisa_hash_apuracao(principal, listaCandidatos[i], &apuracao[i]);
	}

	free(aux);
	free(aux2);
}
