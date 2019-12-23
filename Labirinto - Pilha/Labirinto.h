#ifndef LABIRINTO_H_INCLUDED
#define LABIRINTO_H_INCLUDED

int direcao(char **lab,lista l,int linha, int coluna,int posL,int posC);
int busca_inicio(char **lab,int linha,int coluna, int *posX, int *posY);
void mover(char **lab,int linha, int coluna);
int verificar_integridade(char **lab,int linha,int coluna);
char menu();
void limpa_tela();
void corrige_string(char *str);

#endif // LABIRINTO_H_INCLUDED
