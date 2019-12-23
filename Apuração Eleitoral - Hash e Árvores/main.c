#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "CedulaEleitoral.h"
#include "Hash_Apuracao.h"
#include "GerenciaEstruturas.h"
#include "Ordenacao.h"
#include "Constantes.h"
#include "Hash_ABP.h"
#include "Hash_AVL.h"
#include "Hash_Duplo.h"




#define AUMENTA 1.5

int main()
{

    setlocale(LC_ALL, "portuguese");

	/*Ponteiro genérico, que vai referenciar uma dos 3 tipos de estrutura (hash duplo, hash de árvore binária ou AVL*/
	void *estrutura;

	tipo_cedula cedula;
	cedula_apuracao *apurar;


	/* Tabelas hash de apuração com resolução de colisão por hash duplo.*/
	hash_apuracao apurarPresidente;
	hash_apuracao apurarSenador;

	/*Armazenam o número dos candidatos que já foram votados.*/
    int *listaPresidentes;
    int *listaSenadores;

    /*Título do eleitor*/
	tipo_chave titulo;

	int cont,tipoEstrutura, acao, classeCandidato,
    	numCandidato, tamRanking, numSenadores,
	    numPresidentes, numEleitores, qtdVotos = 0, modo;

	FILE *arqEntrada;
    arqEntrada = fopen("entrada.txt", "r+");

	// Pega o modo que o programa será executado: O - Simulação 1 - Campeonato
	fscanf(arqEntrada, "%d", &modo);

	switch(modo){
		case 0: // Simulação

				fscanf(arqEntrada, "%d", &tipoEstrutura);

			    fscanf(arqEntrada, "%d %d %d", &numSenadores, &numPresidentes, &numEleitores);



			    estrutura =(void*) criaEstrutura((numEleitores * 2),tipoEstrutura);

			    apurarPresidente = criarTHDApuracao(numPresidentes * AUMENTA);
				apurarSenador = criarTHDApuracao(numSenadores * AUMENTA);
				listaPresidentes = (int*)malloc(sizeof(int) * numPresidentes);
				listaSenadores = (int*)malloc(sizeof(int) * numSenadores);


				do{
					//Pega a ação a ser executada
					fscanf(arqEntrada, "%d", &acao);

					switch(acao){
						
						case 0: //Inserir

							fscanf(arqEntrada, "%d %s %d", &classeCandidato, titulo, &numCandidato);

							strcpy(cedula.tituloEleitor, titulo);

							if(classeCandidato == 0){
								cedula.votoPresidente = numCandidato;
								cedula.votoSenador = 0;
							}
							else{
								cedula.votoSenador = numCandidato;
								cedula.votoPresidente = 0;
							}

							if(inserirItemEstrutura(estrutura, cedula, tipoEstrutura)){
                                qtdVotos++;
								apurar = (cedula_apuracao*)malloc(sizeof(cedula_apuracao));

								if(classeCandidato == 0){
									insere_hash_apuracao(apurarPresidente, numCandidato, listaPresidentes, &apurar->numVotos);
									pesquisa_hash_apuracao(apurarPresidente, numCandidato, apurar);
									printf("\nVoto computado! Presidente [%d] tem %d voto(s)", apurar->numCandidato, apurar->numVotos);
								}

								else{
									insere_hash_apuracao(apurarSenador, numCandidato, listaSenadores, &apurar->numVotos);
									pesquisa_hash_apuracao(apurarSenador, numCandidato, apurar);
									printf("\nVoto computado! Senador  [%d] tem %d voto(s)", apurar->numCandidato, apurar->numVotos);


								}

                                free(apurar);
							}
							else
								printf("\nVoto não computado! %d voto(s) válido(s)", qtdVotos);
							break;


							
							case 1: // Remover
								fscanf(arqEntrada, "%s", titulo);
								if(removerItemEstrutura(estrutura, titulo, &cedula, tipoEstrutura)){
			                    	qtdVotos--;
									printf("\nMeliante removido :: %d votos válido(s) no sistema", qtdVotos);
			                    	apurar = (cedula_apuracao*)malloc(sizeof(cedula_apuracao));

			                    	if(cedula.votoPresidente != -1){
			                        	remove_hash_apuracao(apurarPresidente, cedula.votoPresidente, apurar);
			                    	}
			                    	if(cedula.votoSenador != -1){
			                        	remove_hash_apuracao(apurarSenador, cedula.votoSenador, apurar);
			                    	}

			                    	free(apurar);
								}
								else
			                    	printf("\nMeliante não removido :: %d votos valido(s) no sistema", qtdVotos);

								break;

							
							case 2: // Apurar
								fscanf(arqEntrada, "%d %d", &classeCandidato, &tamRanking);
								apurar =(cedula_apuracao*)malloc(sizeof(cedula_apuracao)*tamRanking);
								char tipoCandidato[20];

								if(tamRanking > 100)
									tamRanking = 100;

								if(classeCandidato == 1){
			                    	strcpy(tipoCandidato, "Presidente");
									selectSort(apurarPresidente, listaPresidentes, apurar, apurarPresidente->quantidade_dados, tamRanking);
									if(tamRanking > apurarPresidente->quantidade_dados)
										tamRanking = apurarPresidente->quantidade_dados;
								}
								else{
			                    	strcpy(tipoCandidato, "Senador");
									selectSort(apurarSenador,listaSenadores, apurar, apurarSenador->quantidade_dados, tamRanking);
									if(tamRanking > apurarSenador->quantidade_dados)
										tamRanking = apurarSenador->quantidade_dados;
							}

                            printf("\n\n --- %s ---", tipoCandidato);
							for(cont = 0; cont < tamRanking; cont++)
                                printf("\nCandidato :: %d %d voto(s)", apurar[cont].numCandidato, apurar[cont].numVotos);

							free(apurar);
							break;
					}
				}while(acao != 3);
				
				if(tipoEstrutura == 0)
						printf("Número de colisões da estrura de Hash Árvore de Pesquisa Binária :: %d", numero_colisoes_hash_abp);
				
				if(tipoEstrutura == 1 )
					printf("Número de colisões da estrura de Hash Duplo :: %d", numero_colisoes_hash_duplo);
				



				free(listaSenadores);
			    free(listaPresidentes);
			    fclose(arqEntrada);
				termina_hash_apuracao(apurarPresidente);
			    termina_hash_apuracao(apurarSenador);
			    terminarEstrutura(estrutura, tipoEstrutura);

				case 1:// Competição
					break;

	}




	return 0;


}
