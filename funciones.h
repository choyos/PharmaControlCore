/*  Trabajo fin de curso de programación 2010*/
/*Apellidos: Hoyos Martín
Nombre: César
Login: ceshoymar */

/*Declaración de funciones de tratamiento de la información recibida*/

#ifndef HORA_H
#define HORA_H

#include "typedef.h"

//Crea un nodo de tipo medicina, con la información leida de la trama.
MEDICINE * CreaNodoMed ( int stock, float precio_med, float precio_alm, float coste_pedido, float coste_recogida, float coste_sin_stock, float coste_oportunidad, int* repartidos, int maxStock, int minStock, int nTamPedidos, int* vTamPedidos, int horizonte);

void EnlazaMedicinas (MEDICINE * medicinaNueva, MEDICINE ** medicinaPrimera);	//Crea la lista de medicinas enlazando, de forma ordenada según criterio a fijar.

void BorraMedicinas (MEDICINE ** medicinaPrimera); //Borra la lista completa de medicinas liberando la memoria.

void ImprimeMedicinas (MEDICINE * pAnterior, int horizonte, int numPedidos);	//Imprime todos los datos de todos los medicamentos leidos

void MatrizCombMedicinas (MEDICINE ** medicinaPrimera, int numPedidos);		//Realiza el calculo de la matriz de combinaciones de las diferentes medicinas y las añade a la estructura

float EvaluaMedicinas(MEDICINE ** medicinaPrimera, int horizonte, int numPedidos, int * posibilidad, int ** matPedidosOptimos, int ** matStockOptimo, float * Jmin);	//Realiza el calculo de coste total

void AlmacenaOptimos(MEDICINE ** medicinaPrimera, int horizonte, int ** matPedidosOptimos, int ** matStockOptimo, float * Jmin);	//Función para almacenar las variables optimas ligadas a los medicamentos

void ImprimeResultados(MEDICINE ** medicinaPrimera, int horizonte);		//Funcion para imprimir de forma presentable los resultados

void BorraMedicina(MEDICINE * medicina);	//Función que borra un medicamento

#endif