/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#ifndef EVALUA_H
#define EVALUA_H
#endif

#include "typedef.h"
#include <time.h>

//Función que evalua cada posibilidad para devolver un coste total de medicamentos
float evalua(int* pedidos, int horizonte, int retraso, int* stock, MEDICINE *med);

//Función para inicializar los vectores a 0
void inicializa(int * v,int tam);
