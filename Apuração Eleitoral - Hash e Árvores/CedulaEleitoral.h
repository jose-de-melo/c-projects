#ifndef CEDULAELEITORAL_H_INCLUDED
#define CEDULAELEITORAL_H_INCLUDED

#include "Constantes.h"

typedef char tipo_chave[9];

typedef struct{
    int votoPresidente , votoSenador;

    tipo_chave tituloEleitor;

}tipo_cedula;


#endif // CEDULAELEITORAL_H_INCLUDED
