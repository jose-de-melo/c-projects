#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "Estruturas.h"
#include "ListaEncadeada.h"

#define INFINITO 1000000
#define MEMBRO 1
#define NAOMEMBRO 0

typedef enum{espera, pronto, processado} tipo_status;

typedef struct{
    tipo_elemento info;
    lista lista_de_adjacencia;
    tipo_status status;
}tipo_vertice;

typedef struct{
    tipo_vertice *vertices;
    int num_vertices, tamanho;
}tipo_grafo;

typedef tipo_grafo *grafo;

grafo cria_grafo(unsigned int);
int pesquisa_vertice(grafo, tipo_chave);
int adiciona_vertice(grafo, tipo_elemento);
int adiciona_aresta(grafo, tipo_chave, tipo_chave, tipo_peso);
int remove_aresta(grafo, tipo_chave, tipo_chave);
int remove_vertice(grafo, tipo_chave);
void termina_grafo(grafo);
int tamanho_grafo(grafo);
int get_num_arestas(grafo);
void imprime_grafo(grafo);
void bfs(grafo, tipo_chave);
void dfs(grafo, tipo_chave);
void agm_prim(grafo, tipo_chave);
int dijkstra(grafo, tipo_chave, tipo_chave);



#endif // GRAFO_H_INCLUDED
