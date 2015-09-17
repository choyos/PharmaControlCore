/*  Trabajo fin de curso de programación 2010*/
/*Apellidos: Hoyos Martín
Nombre: César
Login: ceshoymar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "typedef.h"
#include "matrices.h"

MEDICINE * CreaNodoMed ( int stock, float precio_med, float precio_alm, float coste_pedido, float coste_recogida, float coste_sin_stock, float coste_oportunidad, int* repartidos, int maxStock, int minStock, int nTamPedidos, int* vTamPedidos, int horizonte)
{
	int i;
	MEDICINE *p = NULL;
	p = (MEDICINE *) malloc(sizeof(MEDICINE));	//Reservamos memoria para la estructura program
	if (p != NULL){
		
		//Inicializamos los siguientes campos de la estructura;
    	p->stock = stock;
    	p->precio_med = precio_med;	
    	p->precio_alm = precio_alm;
    	p->coste_pedido = coste_pedido;
    	p->coste_recogida = coste_recogida;
    	p->coste_sin_stock = coste_sin_stock;
    	p->coste_oportunidad = coste_oportunidad;
    	p->repartidos = (int*) malloc( horizonte * sizeof(int));
    	for(i = 0; i<horizonte; i++)
    		p->repartidos[i] = repartidos[i];
    	p->maxStock = maxStock;
    	p->minStock = minStock;
    	p->nTamPedidos = nTamPedidos;
    	p->vTamPedidos = (int*) malloc((nTamPedidos+1) * sizeof(int));
    	for(i = 0; i<nTamPedidos; i++)
    		p->vTamPedidos[i] = vTamPedidos[i];
    	p->vTamPedidos[nTamPedidos] = 0;
    	p->sig = NULL;				//el puntero al siguiente programa de la lista a NULL.
    }
  return p;
}

void EnlazaMedicinas (MEDICINE * medicinaNueva, MEDICINE ** medicinaPrimera)	//Esta funcion enlaza los programas ordenados segun su hora de inicio
{
	MEDICINE * anterior = NULL;
	MEDICINE * primero = *medicinaPrimera;	//esta asignacion nos permite guardar el primer nodo de la lista	
	
	while ( *medicinaPrimera != NULL)
	{	
		anterior = (*medicinaPrimera);	//esta asignacion nos permitira almacenar el valor del nodo anterior, que es tras el que ira enlazado nuestro nuevo programa
		*medicinaPrimera = (*medicinaPrimera)->sig;	//seguimos recorriendo la lista
	}
	
	if( anterior == NULL) 
	{
		medicinaNueva->sig = *medicinaPrimera;
		*medicinaPrimera = medicinaNueva;
	}
	else
	{
		anterior->sig = medicinaNueva;
		medicinaNueva->sig = *medicinaPrimera;
		*medicinaPrimera = primero;
	}
}

void BorraMedicinas (MEDICINE ** medicinaPrimera){
  MEDICINE *paux = NULL;
  while (*medicinaPrimera != NULL)
  {
    paux = *medicinaPrimera;
    *medicinaPrimera = paux->sig;
	if( paux->repartidos != NULL)			
		liberaVector(paux->repartidos);
	if( paux->vTamPedidos != NULL)			
		liberaVector(paux->vTamPedidos);
	if(paux->matrixComb != NULL)
		liberaMatriz(paux->filasMatrixComb, paux->matrixComb);

    free(paux);
  }
}

void ImprimeMedicinas (MEDICINE * pAnterior, int horizonte)
{
	int i = 0;
	int j;
	while (pAnterior != NULL)
	{
		i++;
		printf("\t=====Medicamento %d=====\n",i );
		printf("\tStock %d:\t\t\t\t%d\n", i, pAnterior->stock);
		printf("\tPrecio medicamento %d:\t\t\t%f\n", i, pAnterior->precio_med);
		printf("\tPrecio almacenamiento %d:\t\t%f\n", i, pAnterior->precio_alm);
		printf("\tCoste pedido %d:\t\t\t\t%f\n", i, pAnterior->coste_pedido);
		printf("\tCoste recoger %d:\t\t\t%f\n", i, pAnterior->coste_recogida);
		printf("\tCoste de quedarnos sin stock %d:\t\t%f\n", i, pAnterior->coste_sin_stock);
		printf("\tCoste oportunidad %d:\t\t\t%f\n", i, pAnterior->coste_oportunidad);
		printf("\tCantidades repartidas %d\t\t\t", i);
		for(j = 0; j<horizonte; j++)
			printf("%d ", pAnterior->repartidos[j]);
		printf("\n\tStock maximo almacenable %d:\t\t%d\n", i, pAnterior->maxStock);
		printf("\tStock minimo de seguridad %d:\t\t%d\n", i, pAnterior->minStock);
		printf("\tPosibilidades de pedido %d:\t\t%d\n", i, pAnterior->nTamPedidos);
		printf("\tCantidades posibles de pedido %d:\t", i);
		for(j = 0; j<pAnterior->nTamPedidos; j++)
			printf("%d ", pAnterior->vTamPedidos[j]);
		printf("\n\n");
		pAnterior = pAnterior->sig;
	}
}