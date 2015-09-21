/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#ifndef MATRICES_H
#define MATRICES_H
#endif

#include "typedef.h"
#include <time.h>

//Función que evalua cada posibilidad para devolver un coste total de medicamentos
void imprimeMatriz(int numFilas, int numColumnas, int **matriz);

void imprimeVector(int dim, int * vector);

//Función para inicializar dinamicamente una matriz
//Debe recibir como entrada para poder definir la matriz
//una dirección de matriz
void inicializaMatriz(int numFilas, int numColumnas, int ***matriz);

//Función para inicializar dinamicamente un vector
void inicializaVector(int dim, int **vector);

//Función para liberar reserva de los vectores de una matriz
void liberaMatriz(int numFilas, int ** matriz);

//Función para liberar reserva de un vector
void liberaVector(int *vector);


//Función para convertir de entero a binario con n bits. Devuelve un vector
void convIntToBin(int num, int bits, int * posibilidad);

//Función para inicializar los vectores a 0
void inicializa(int * v,int tam);

void imprimeNumPunteros();