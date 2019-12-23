#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Grafo.h"



grafo cria_grafo(unsigned int t){
    int i, k;

    grafo g = (grafo) malloc(sizeof(tipo_grafo));
    if(g){


        g->vertices = (tipo_vertice*) malloc(sizeof(tipo_vertice) * t);

        if(g->vertices){
            g->num_vertices = 0;
            g->tamanho = t;


            for(i = 0; i < t; i++){
                g->vertices[i].lista_de_adjacencia = cria_lista();
                if(!g->vertices[i].lista_de_adjacencia)
                    break;
            }


            if(i < t){
                for(k = 0; k < i; k++){
                    termina_lista(g->vertices[i].lista_de_adjacencia);
                }
                free(g->vertices);
                free(g);
                g = NULL;
            }
            else{

                for(i = 0; i < t; i++)
                    g->vertices[i].status = espera;
            }
        }
        else{
            free(g);
            g = NULL;
        }
    }
    return g;
}


int pesquisa_vertice(grafo g, tipo_chave ch){
    int i;

    for(i = 0; i < g->num_vertices; i++)
        if(strcmp(g->vertices[i].info.chave, ch) == 0)
            return i;
    return -1;
}


int adiciona_vertice(grafo g, tipo_elemento e){
    if(g->num_vertices == g->tamanho)
        return 0;
    if(pesquisa_vertice(g, e.chave) != -1)
        return 0;
    g->vertices[g->num_vertices].info = e;
    g->vertices[g->num_vertices].status = espera;
    g->num_vertices++;
    return 1;
}


int adiciona_aresta(grafo g, tipo_chave ch1, tipo_chave ch2, tipo_peso p){
    int i, k;
    tipo_elemento_lista e;


    i = pesquisa_vertice(g, ch1);
    if(i == -1)
        return 0;
    k = pesquisa_vertice(g, ch2);
    if(k == -1)
        return 0;


    if (pesquisa_elemento(g->vertices[i].lista_de_adjacencia, ch2))
        return 0;

    strcpy(e.chave, ch2);
    e.peso = p;
    if(insere_lista_ordenada(g->vertices[i].lista_de_adjacencia, e)) {
        strcpy(e.chave, ch1);
        e.peso = p;
        if(!insere_lista_ordenada(g->vertices[k].lista_de_adjacencia, e))
            remove_elemento(g->vertices[i].lista_de_adjacencia, 1);
        else
            return 1;
    }
    return 0;
}


int remove_aresta(grafo g, tipo_chave ch1, tipo_chave ch2){
    int i, k, a1, a2;


    i = pesquisa_vertice(g, ch1);
    if(i == -1)
        return 0;
    k = pesquisa_vertice(g, ch2);
    if(k == -1)
        return 0;

    a1 = pesquisa_elemento(g->vertices[i].lista_de_adjacencia, ch2);
    if(a1 == 0)
        return 0;
    a2 = pesquisa_elemento(g->vertices[k].lista_de_adjacencia, ch1);
    if(a2 == 0)
        return 0;


    if(remove_elemento(g->vertices[i].lista_de_adjacencia, a1))
        if(remove_elemento(g->vertices[k].lista_de_adjacencia, a2))
            return 1;
    return 0;
}


int remove_vertice(grafo g, tipo_chave ch){
    int i, k, a;

    i = pesquisa_vertice(g, ch);
    if(i == -1)
        return 0;

    for(k = 0; k < g->num_vertices; k++)
        if (k != i){
            a = pesquisa_elemento(g->vertices[k].lista_de_adjacencia, ch);
            if (a != 0)
                remove_elemento(g->vertices[k].lista_de_adjacencia, a);
        }

    termina_lista(g->vertices[i].lista_de_adjacencia);

    if (i != (g->num_vertices - 1))
        g->vertices[i] = g->vertices[(g->num_vertices - 1)];
    g->vertices[(g->num_vertices - 1)].lista_de_adjacencia = cria_lista();
    g->num_vertices--;
    return 1;
}

void termina_grafo(grafo g){
    int i;

    if(g){
        for(i = 0; i < g->tamanho; i++)
            termina_lista(g->vertices[i].lista_de_adjacencia);
        free(g->vertices);
        free(g);
    }
}


int tamanho_grafo(grafo g){
    return g->num_vertices;
}


int get_num_arestas(grafo g){
    int i, count = 0;

    for (i = 0; i < g->num_vertices; i++){
        count += tamanho_lista(g->vertices[i].lista_de_adjacencia);
    }
    return count;
}


void imprime_grafo(grafo g){
    int i, k;
    tipo_elemento_lista e;

    printf("\n Grafo:\n");
    for(i = 0; i < g->num_vertices; i++){
        printf("\n * %s --> ", g->vertices[i].info.chave);
        k = 1;
        while(get_elemento(g->vertices[i].lista_de_adjacencia, &e, k)){
            printf("%s: (%d) --> ", e.chave, e.peso);
            k++;
        }
        printf("fim\n");
    }
}



int dijkstra(grafo g, tipo_chave origem, tipo_chave destino){
    int *dist, *per, *path;
    int corrente, s, t, i, k, dc, j;
    int menor_dist, nova_dist,caminho;
    tipo_elemento_lista el;

    dist = (int*) malloc(sizeof(int) * g->tamanho);
    per = (int*) malloc(sizeof(int) * g->tamanho);
    path = (int*) malloc(sizeof(int) * g->tamanho);
    for (i = 0; i < g->num_vertices; i++) {
        per[i] = NAOMEMBRO;
        dist[i] = INFINITO;
    }
    s = pesquisa_vertice(g, origem);
    t = pesquisa_vertice(g, destino);
    if(s == -1 || t == -1)
        return 0;
    per[s] = MEMBRO;
    dist[s] = 0;
    corrente = s;
    k = corrente;

    while (corrente != t){
        menor_dist = INFINITO;
        dc = dist[corrente];
        for (i = 0; i < g->num_vertices; i++){
            j = pesquisa_elemento(g->vertices[corrente].lista_de_adjacencia, g->vertices[i].info.chave);
            if (per[i] == NAOMEMBRO && j != 0){
                get_elemento(g->vertices[corrente].lista_de_adjacencia, &el, j);
                nova_dist = dc + el.peso;
                if (nova_dist < dist[i]){
                    dist[i] = nova_dist;
                    path[i] = corrente;
                }
            }
        }
        menor_dist = INFINITO;
        for (i = 0; i < g->num_vertices; i++){
            if (per[i] == NAOMEMBRO && dist[i] < menor_dist){
                k = i;
                menor_dist = dist[i];
            }
        }
        corrente = k;
        per[corrente] = MEMBRO;
    }
    printf("\nResultado: ");
    caminho = t;
    printf("%s", g->vertices[t].info.chave);

    while (caminho != s){
        if (caminho != s)
            printf (" -> ");
        printf("%s", g->vertices[(path[caminho])].info.chave);
        caminho = path[caminho];
    }
    printf("\nDistancia: %d km\n\n ", dist[t]);
    free(dist);
    free(per);
    free(path);
    return 1;
}
