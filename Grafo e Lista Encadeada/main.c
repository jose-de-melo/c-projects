#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

void limpaTela(){
    if (system("cls"))
        system("clear");
}


void menu(){
    limpaTela();
    printf("\n\t1 - Gerar Grafo");
    printf("\n\t2 - Inserir vertices (elementos)");
    printf("\n\t3 - Inserir arestas");
    printf("\n\t4 - Imprimir grafo");
    printf("\n\t0 - Sair.");
    printf("\n\n\n\tOpcao desejada ::  ");
}

void criar_grafo(grafo *g){
    int tamanho = 0;
    limpaTela();

    printf("\n\n\tTamanho do grafo: ");
    scanf("%d", &tamanho);

    if(tamanho <= 0)
        printf("\n\nTamanho inválido!");
    else{
        (*g) = cria_grafo(tamanho);
        printf("\n\nTecle ENTER para continuar...");
        getchar();
    }
}

void insere_elementos(grafo *g){
    char chave[100];
    tipo_elemento e;

    if(g == NULL)
        return;

    do{ limpaTela();
        printf("\nDigite 0 para sair!\n\n");

        printf("\n\tDigite a chave (char): ");
        setbuf(stdin, NULL);
        scanf("%s", chave);

        if(strcmp(chave, "0") == 0) return;

        strcpy(e.chave, chave);
        adiciona_vertice(*g, e);

        setbuf(stdin, NULL);
    }while(strcmp(chave, "0") != 0);
}

void insere_arestas(grafo *g){
    tipo_chave aresta1;
    tipo_chave aresta2;
    int peso = 0;

    if(*g == NULL)
        return;

    do{ limpaTela();
        printf("\nDigite 0 para sair!\n\n");

        printf("\n\tDigite a 1a aresta (char): ");
        setbuf(stdin, NULL);
        scanf("%s", aresta1);

        if(strcmp(aresta1, "0") == 0) return;

        printf("\n\tDigite a 2a aresta (char): ");
        setbuf(stdin, NULL);
        scanf("%s", aresta2);

        if(strcmp(aresta2, "0") == 0) return;

        printf("\n\tDigite o peso (int): ");
        scanf("%d", &peso);

        adiciona_aresta(*g, aresta1, aresta2, peso);

        setbuf(stdin, NULL);
    }while(strcmp(aresta1, "0") != 0 || strcmp(aresta2, "0") != 0 );
}

int main(){
    int opcao;
    grafo g;

    do{
        menu();
        scanf("%d", &opcao);


        switch (opcao){
            case 1: criar_grafo(&g); break;
            case 2: insere_elementos(&g); break;
            case 3: insere_arestas(&g); break;
            case 4: imprime_grafo(g);  getchar(); break;
        }

        if(opcao !=0 ) getchar();

    }while (opcao != 0);

    termina_grafo(g);
   return 0;
}
