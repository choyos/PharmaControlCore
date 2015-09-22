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
#include "evalua.h"
#include "fechas.h"

MEDICINE * CreaNodoMed ( int stock, float precio_med, float precio_alm, float coste_pedido, float coste_recogida, float coste_sin_stock, float coste_oportunidad, int* repartidos, int maxStock, int minStock, int nTamPedidos, int* vTamPedidos, int horizonte)
{
	int i;
	MEDICINE *p = NULL;
	p = (MEDICINE *) malloc(sizeof(MEDICINE));	//Reservamos memoria para la estructura MEDICINE
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
    	//Inicializamos los vectores del medicamento
		inicializaVector(horizonte, &(p->pedidosOptimos));
		inicializaVector(horizonte, &(p->stockOptimo));
    }
  return p;
}

void BorraMedicina(MEDICINE * medicina){

	//Liberamos memoria de vectores y matrices
	if( medicina->repartidos != NULL)			
		liberaVector(medicina->repartidos);
	if( medicina->vTamPedidos != NULL)			
		liberaVector(medicina->vTamPedidos);
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


void ImprimeMedicinas (MEDICINE * pAnterior, int horizonte, int numPedidos)
{
	int i = 0;
	int j;
	int x;
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
		printf("\n\tFilas de la matriz de combinaciones %d: \t%d\n", i, pAnterior->filasMatrixComb);
		printf("\tMatriz de combinaciones %d:\t\t", i);
	//	imprimeMatriz(pAnterior->filasMatrixComb, numPedidos, pAnterior->matrixComb);

		for(x=0;x<pAnterior->filasMatrixComb;x++){
			for(j=0;j<numPedidos;j++){
				printf("%d ",pAnterior->matrixComb[x][j]);
			}
			printf("\n");
			printf("\t\t\t\t\t\t");
		}

		printf("\n\n");
		pAnterior = pAnterior->sig;
	}
}

void MatrizCombMedicinas (MEDICINE ** medicinaPrimera, int numPedidos){
	
	MEDICINE * paux = NULL;
	MEDICINE * primero = *medicinaPrimera;
	
	int j;
	int i;

	int divisor;


	
	while(*medicinaPrimera != NULL){
		
		paux = *medicinaPrimera;
		*medicinaPrimera = paux->sig;

		paux->filasMatrixComb = 1;
		for(i=0;i<numPedidos;i++){
			paux->filasMatrixComb=(paux->filasMatrixComb)*(paux->nTamPedidos);
		}

		divisor = (paux->filasMatrixComb)/(paux->nTamPedidos); //Variable auxiliar para acceder al vector de la forma adecuada
		//Matriz de combinaciones
		inicializaMatriz((paux->filasMatrixComb), numPedidos, &(paux->matrixComb));
		
		for(j=0;j<numPedidos;j++){	//Luego por filas
			for(i=0;i<(paux->filasMatrixComb);i++){	//Primero por columnas
				paux->matrixComb[i][j]=paux->vTamPedidos[(i/divisor)%(paux->nTamPedidos)];
			}
			divisor=divisor/(paux->nTamPedidos);	//Disminuimos la auxiliar para acceder a la posicion correcta
		}
	}
	//Recuperamos la referencia de la lista
	*medicinaPrimera = primero;
}

void BorraMedicinas (MEDICINE ** medicinaPrimera){
  
  //Puntero auxiliar para recorrido de lista
  MEDICINE *paux = NULL;
  
  while (*medicinaPrimera != NULL){
  	//Recorremos la lista
    paux = *medicinaPrimera;
    *medicinaPrimera = paux->sig;
	
    //Liberamos memoria de vectores y matrices
	if( paux->repartidos != NULL)			
		liberaVector(paux->repartidos);
	if( paux->vTamPedidos != NULL)			
		liberaVector(paux->vTamPedidos);
	if(paux->matrixComb != NULL)
		liberaMatriz(paux->filasMatrixComb, paux->matrixComb);
	if(paux->pedidosOptimos != NULL)
		liberaVector(paux->pedidosOptimos);
	if(paux->stockOptimo != NULL)
		liberaVector(paux->stockOptimo);

	//Liberamos la referencia del nodo eliminandolo
    free(paux);
  }
}

float EvaluaMedicinas(MEDICINE ** medicinaPrimera, int horizonte, int numPedidos, int * posibilidad, int ** matPedidosOptimos, int ** matStockOptimo, float * Jmin){
	
	MEDICINE * paux = NULL;	//Puntero auxiliar para recorrer la lista
	MEDICINE * primero = *medicinaPrimera;	//Puntero para no perder la referencia del comienzo de la lista

	//Matriz auxiliar para las combinaciones
	int ** matrix;

	//Variables auxiliares
	int i = 0;
	int x;
	int j;
	int k;
	int g = 0;

	//Variables auxiliares para el computo
	int *stock;
	float J;
	float Jtotal;

	//Inicializamos los vectores y matrices necesarios
	inicializaMatriz(primero->filasMatrixComb, horizonte, &matrix);
	inicializaVector(horizonte, &stock);

	while(*medicinaPrimera != NULL){

		//Recorremos la lista
		paux = *medicinaPrimera;
		*medicinaPrimera = paux->sig;

		/*Generamos la matriz para evaluar las diferentes posibilidades de pedido*/
		for(k = 0; k < paux->filasMatrixComb; k++){		// Accedemos todas las veces de las combinaciones posibles
			for(j = 0; j < horizonte; j++){		// En el recorrido
				if( posibilidad[j] == 1){	// Si es 1 se cambia por el valor correspondiente
					matrix[k][j] = posibilidad[j] * paux->matrixComb[k][g];
					g++;
					
				}else{	//Si es 0 se deja igual
					matrix[k][j] = posibilidad[j];
				}							
			}
			g=0;	//Al finalizar cada pasada reiniciamos el contador g a 0
		}
		
		/*Realizamos el computo con todas las posibilidades de la matriz obteniendo las Js*/
		for(x = 0; x < paux->filasMatrixComb; x++){
			inicializa(stock, horizonte);
			J = evalua(matrix[x], horizonte, 0, stock, paux);
		//	printf("\n%d->\tJ = %f\n",x,J);
			if(x == 0 || J < Jmin[i]){
				Jmin[i] = J;
				for(k=0; k<horizonte; k++){
					matStockOptimo[i][k] = stock[k];
					matPedidosOptimos[i][k] = matrix[x][k];
				}
			}
		}
		
		//Sum(Jmin_i) Sumamos los minimos de los medicamentos
		Jtotal = Jtotal + Jmin[i];

		i++;
	}
		
	/*Añadimos los costes de pedido y recogida (el ahorro real respecto 
	al computo de medicamentos de forma individual)*/
	Jtotal = Jtotal + numPedidos * (primero->coste_pedido + primero->coste_recogida);

	//Recuperamos la referencia del principio
	*medicinaPrimera = primero;

	//Liberamos memoria de matrices y vectores reservados
	liberaMatriz(primero->filasMatrixComb, matrix);
	liberaVector(stock);

	//Devolvemos el resultado de evaluar todos 
	return Jtotal;
}

void AlmacenaOptimos(MEDICINE ** medicinaPrimera, int horizonte, int ** matPedidosOptimos, int ** matStockOptimo, float * Jmin){

	//Variables para recorrido de lista
	MEDICINE * paux = NULL;
	MEDICINE * primero = *medicinaPrimera;

	//Variables auxiliares
	int i = 0;
	int j;

	while( *medicinaPrimera != NULL){

		//Recorremos la lista
		paux = *medicinaPrimera;
		*medicinaPrimera = paux->sig;

		paux->Jmin = Jmin[i];
		for(j = 0; j < horizonte; j++){
			paux->pedidosOptimos[j] = matPedidosOptimos[i][j];
			paux->stockOptimo[j] = matStockOptimo[i][j];
		}

		i++;
	}

	//Recuperamos la referencia del principio de la lista
	*medicinaPrimera = primero; 
}

void ImprimeResultados(MEDICINE ** medicinaPrimera, int horizonte, float Jtotal){

	//Punteros para recorrido de lista
	MEDICINE * paux = NULL;
	MEDICINE * primero = *medicinaPrimera;

	//Variables auxiliares
	int i = 0;
	int j;
	int numPedidos;

	printf("\t================\n");
	printf("\t===Resultados===\n");
	printf("\t================\n");
	printf("\n\tCoste total: %.2f\n\n", Jtotal);

	while(*medicinaPrimera != NULL){

		numPedidos = 0;

		//Incrementamos el contador auxiliar
		i++;

		//Recorremos la lista
		paux = *medicinaPrimera;
		*medicinaPrimera = paux->sig;

		printf("\tMedicamento %d\n", i);
		printf("\tStock Optimo %d:\t\t",i);
		imprimeVector(horizonte, paux->stockOptimo);
		printf("\n\tPedidos optimos %d:\t",i);
		imprimeVector(horizonte, paux->pedidosOptimos);
		printf("\n");
		for(j=0;j<horizonte; j++){
			if(paux->pedidosOptimos[j] != 0){
				numPedidos++;
			}
		}

		/*Función de fechas.c que muestra por pantalla de forma ordenada 
		cuando y cuanto hay que solicitar*/
		printf("\tFechas de pedido %d:\n", i);
		obtieneFechasPedidos(paux->pedidosOptimos, horizonte, numPedidos);
		printf("\n");
	}

	//Recuperamos la referencia
	*medicinaPrimera = primero;
}