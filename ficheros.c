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
#include "ficheros.h"
#include "matrices.h"

#define LUNES 0
#define MARTES 1
#define MIERCOLES 2
#define JUEVES 3
#define VIERNES 4
#define SABADO 5
#define DOMINGO 6

#define TAM_BUF 100

int ficheros(int horizonte, MEDICINE* med){
	FILE *fp;
	int i;
	int error = 0;	//Variable de error

	fp = fopen ( "datos.pha" , "r" );
	if(fp == NULL){	//Caso de no apertura pasar el error 
		error = -1;
	}else{	//Caso de apertura
		
		/*1- Lectura del stock actual*/
		fscanf(fp, "%d", &(med->stock));
		/*2- Lectura del precio del medicamento*/
		fscanf(fp, "%f", &(med->precio_med));
		/*3- Lectura del precio del almacenaje*/
		fscanf(fp, "%f", &(med->precio_alm));
		/*4- Lectura del precio del coste de pedido*/
		fscanf(fp, "%f", &(med->coste_pedido));
		/*5- Lectura del precio del coste de recogida*/
		fscanf(fp, "%f", &(med->coste_recogida));
		/*6- Lectura del precio del coste por quedarse sin medicamentos*/
		fscanf(fp, "%f", &(med->coste_sin_stock));
		/*7- Lectura del precio del coste de oportunidad*/
		fscanf(fp, "%f", &(med->coste_oportunidad));
		/*8- Lectura de la estimacion de repartidos*/
		inicializaVector(horizonte, &(med->repartidos));
		for(i=0; i<horizonte;i++){ 
			fscanf(fp, "%d", med->repartidos+i );
		}
		/*9+horizonte- Lectura del maximo stock almacenable*/
		fscanf(fp, "%d", &(med->maxStock));
		/*10+horizonte- Lectura del minimo stock almacenable*/
		fscanf(fp, "%d", &(med->minStock));
		/*11+horizonte- Lectura del numero de posibles pedidos*/
		fscanf(fp, "%d", &(med->nTamPedidos));
		/*12+horizonte- Lectura del vector de posibles pedidos*/
		inicializaVector(med->nTamPedidos, &(med->vTamPedidos));
		for(i=0; i<med->nTamPedidos;i++){ 
			fscanf(fp, "%d", med->vTamPedidos+i );
		}
		fclose ( fp );
	}
	
	return error;
}