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
#include "matrices.h"

#define LUNES 0
#define MARTES 1
#define MIERCOLES 2
#define JUEVES 3
#define VIERNES 4
#define SABADO 5
#define DOMINGO 6

#define TAM_BUF 100

int liberaM = 0;
int liberaV = 0;
int inicializaM = 0;
int inicializaV = 0;


void imprimeMatriz(int numFilas, int numColumnas, int **matriz){

	
	int i;	//Variable auxiliar para recorrer filas
	int j;	//Variable auxiliar para recorrer columnas

	for(i=0;i<numFilas;i++){
		printf("\t");
		for(j=0;j<numColumnas;j++){
			printf("%d ",matriz[i][j]);
		}
	printf("\n");
	}
}

void imprimeVector(int dim, int * vector){
	int i;

	for(i = 0; i < dim; i++){
		printf("%d ", vector[i]);
	}
}

void inicializaMatriz(int numFilas, int numColumnas, int ***matriz){
	inicializaM++;

	int i;
	(*matriz)=(int **) malloc(numFilas*sizeof(int*));
	for(i=0;i<numFilas;i++){
		(*matriz)[i]=(int *) malloc(numColumnas*sizeof(int));
	}
}

void inicializaVector(int dim, int **vector){
	inicializaV++;
	(*vector) = (int*) malloc(dim*sizeof(int));
}

void liberaMatriz(int numFilas, int ** matriz){

	liberaM++;
	int i;

	for(i = 0; i < numFilas; i++){
		free(matriz[i]);
		matriz[i] = NULL;
	}
	free(matriz);
	matriz = NULL;
}

void liberaVector(int *vector){
	liberaV++;
	free(vector);
	vector = NULL;
}

void convIntToBin(int num, int bits,int *posibilidad){

	int i = 0;

	while(num>1){
		posibilidad[i] = num%2;
		num = num/2;
		i++;
	}
	posibilidad[i] = num;
	for(i = i+1; i<bits; i++){
		posibilidad[i] = 0;
	}
	
}

void inicializa(int * v,int tam){
	int x;
	for(x=0; x < tam; x++){
		v[x] = 0;
	}
}

void imprimeNumPunteros(){
	printf("PUNTEROS\n");
	printf("Reservados %d punteros de matrices\n", inicializaM);
	printf("Reservados %d punteros de vectores\n", inicializaV);
	printf("Liberados %d punteros de matrices\n", liberaM);
	printf("Liberados %d punteros de vectores\n", liberaV);
}