/*  Trabajo fin de curso de programación 2010*/
/*Apellidos: Hoyos Martín
Nombre: César
Login: ceshoymar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "typedef.h"

MEDICINE * CreaNodoMed ( char* med_name,char* code, int stock, float precio_med, float precio_alm, float coste_pedido, float coste_recogida, float coste_sin_stock, float coste_oportunidad, int* repartidos, int maxStock, int minStock, int nTamPedidos, int* vTamPedidos)
{
	MEDICINE *p = NULL;
	p = (MEDICINE *) malloc(sizeof(MEDICINE));	//Reservamos memoria para la estructura program
	if (NULL != p)
    {
		p->programa = (char*)malloc( ( strlen(programa)+1) * sizeof(char));	//Reservamos memoria para la tabla de caracteres que lleva el nombre del programa
    	strcpy( p->programa, programa);	//Copiamos en el campo programa de esta estructura, la cadena de caracteres leida en la trama.
      
    	p->genero = (char*)malloc( ( strlen(genero)+1) * sizeof(char));	//idem que con programa
    	strcpy( p->genero, genero);
		
		//Inicializamos los siguientes campos de la estructura;
    	p->horaInicio = horaInicio;	//hora de comienzo
    	p->minInicio = minInicio;	//minuto de comienzo
    	p->horaFin = horaFin;		//hora en el que finaliza
    	p->minFin = minFin;			//minuto en el que finaliza
    	p->sig = NULL;				//el puntero al siguiente programa de la lista a NULL.
    }
  return p;
}

void EnlazaMedicinas (MEDICINE * medicinaNueva, MEDICINE ** medicinaPrimera)	//Esta funcion enlaza los programas ordenados segun su hora de inicio
{
	int comp = 0;
	int salir = 0;
	MEDICINE * anterior = NULL;
	MEDICINE * primero = *medicinaPrimera;	//esta asignacion nos permite guardar el primer nodo de la lista	
	
	while ( *anterior != NULL && !salir)
	{	
		comp = ComparaProgramas( **medicinaPrimera, *medicinaNueva);	//comparamos los programas con la funcion anterior
	
		if( comp > 0) //si nos ha devuelto un numero positivo, salimos de la funcion
			salir = 1;
		
		else	// en caso contrario
		{
			anterior = (*medicinaPrimera);	//esta asignacion nos permitira almacenar el valor del nodo anterior, que es tras el que ira enlazado nuestro nuevo programa
			*medicinaPrimera = (*medicinaPrimera)->sig;	//seguimos recorriendo la lista
		}
		
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
    *ppAnterior = paux->sig;
	if( paux->repartidos != NULL)			
		free( paux->repartidos);
	if( paux->vTamPedidos != NULL)			
		free( paux->vTamPedidos);
	if( paux->med_name != NULL)
		free(paux->med_name);
	if(paux->code != NULL)
		free(paux->code);

    free(paux);
  }
}