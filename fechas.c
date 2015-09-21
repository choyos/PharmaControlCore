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

int bisiesto(int year){
	int bis;
	bis=(year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	return bis;
}

void obtieneFechasPedidos(int * v, int tam, int numPedidos){
	int x;
	int j=0;

	int ** FechasPedido;


	inicializaMatriz(numPedidos, 3, &FechasPedido);

	for(x=0; x<tam; x++){
		if(v[x]!=0){
			fechaPedido(x, FechasPedido[j]);
			printf("\t%d/%d/%d\n", FechasPedido[j][0], FechasPedido[j][1], FechasPedido[j][2]);
			printf("\t%d\n", v[x]);
			j++;
		}
	}

	liberaMatriz(numPedidos, FechasPedido);
}

/*
	Funcion que recibe un vector y devuelve los campos del mismo
	rellenos con {día, mes, año} en formato entero.
*/
void fechaHoy(int * fechaActual){
	time_t t;
	struct tm *tm;
	char fechayhora[100];
	
	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%d/%m/%Y", tm);
	int i;
	int j=0;
	int k=0;
	char auxFecha[5];
	
	for(i=0;fechayhora[i]!='\0';i++){
		auxFecha[k]=fechayhora[i];
		k++;
		if(fechayhora[i]=='/'){
			auxFecha[k]='\0';
			fechaActual[j]=atoi(auxFecha);
			j++;
			k=0;
		}
	}
	auxFecha[k]='\0';
	fechaActual[j]=atoi(auxFecha);
}

void fechaPedido(int dia, int* fecha){
	int diasMes;
	int *fechaActual;
	inicializaVector(3, &fechaActual);
	int i;

	//Obtenemos hoy
	fechaHoy(fechaActual);
	//Al día de hoy le añadimos los días en los que se pide
	for(i=0; i<3; i++){
		if(i==0){
			fecha[i]=fechaActual[i]+dia;
		}else{
			fecha[i]=fechaActual[i];
		}
	}

	liberaVector(fechaActual);

	//Procedemos a comprobar que la fecha obtenida es correcta en funcion del número
	//de días que tiene cada mes para ver las correcciones a realizar.
	switch (fecha[1]){
		case 1:
			diasMes = 31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 2:
			if(bisiesto(fecha[2])==1){
				diasMes=29;
				if(fecha[0]>diasMes){
					fecha[0]=fecha[0]-diasMes;
					fecha[1]++;
				}
			}
			else{
				diasMes=28;
				if(fecha[0]>diasMes){
					fecha[0]=fecha[0]-diasMes;
					fecha[1]++;
				}
			}
			break;
		case 3:
			diasMes=31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 4:
			diasMes=30;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 5:
			diasMes=31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 6:
			diasMes=30;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 7:
			diasMes=31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 8:
			diasMes=31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 9:
			diasMes=30;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 10:
			diasMes=31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 11:
			diasMes=30;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]++;
			}
			break;
		case 12:
			diasMes=31;
			if(fecha[0]>diasMes){
				fecha[0]=fecha[0]-diasMes;
				fecha[1]=1;
				fecha[2]++;
			}
			break;
		default:
			break;
	}
}