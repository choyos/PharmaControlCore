/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include <time.h>
#include "evalua.h"
#include "fechas.h"
#include "matrices.h"

#define LUNES 0
#define MARTES 1
#define MIERCOLES 2
#define JUEVES 3
#define VIERNES 4
#define SABADO 5
#define DOMINGO 6

#define TAM_BUF 100

float evalua(int* pedidos, int horizonte, int retraso, int* stock, MEDICINE *med){
	//Inicializacion de variables
	int k;
	float J = 0;
	int noStock;


	//Calculo de J y stock
	for(k=0;k<horizonte;k++){
		if(k==0){
			stock[k]=med->stock+pedidos[k];
		//	printf("%d\n",*stock[k] );
		}else{
			stock[k]=stock[k-1]+pedidos[k-retraso]-med->repartidos[k];
		}

		/* 
			Tenemos en cuenta la restricción de que el stock 
			no puede ser menor a una cantidad dada.
		*/
		if((stock[k])<med->minStock){
			noStock = 1;
			stock[k]=stock[k]+minimo(med->nTamPedidos, med->vTamPedidos);
			pedidos[k]=minimo(med->nTamPedidos, med->vTamPedidos);
		}else{
			noStock = 0;
		}
		J = J+med->precio_med*pedidos[k]+(med->precio_alm+med->coste_oportunidad)*stock[k]+noStock*(med->coste_sin_stock);
	}
	
	return J;
}

int minimo(int dim, int * vector){
	int i;
	int minimo;
	for(i = 0; i<dim; i++){
		if(i == 0 && vector[i] != 0){
			minimo = vector[i];
		}else if(vector[i] < minimo && vector[i] != 0){
			minimo = vector[i];
		}
	}
	return minimo;
}