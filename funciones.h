/*  Trabajo fin de curso de programación 2010*/
/*Apellidos: Hoyos Martín
Nombre: César
Login: ceshoymar */

/*Declaración de funciones de tratamiento de la información recibida*/

#ifndef HORA_H
#define HORA_H

#include "typedef.h"

//Crea un nodo de tipo medicina, con la información leida de la trama.
MEDICINE * CreaNodoMed ( char* med_name,char* code, int stock, float precio_med, float precio_alm, float coste_pedido, float coste_recogida, float coste_sin_stock, float coste_oportunidad, int* repartidos, int maxStock, int minStock, int nTamPedidos, int* vTamPedidos);

void EnlazaMedicinasOrdenadas (MEDICINE * medicinaNueva, MEDICINE ** medicinaPrimera);	//Crea la lista de medicinas enlazando, de forma ordenada según criterio a fijar.

void BorraMedicinas (MEDICINE ** medicinaPrimera); //Borra la lista completa de medicinas liberando la memoria.

#endif
