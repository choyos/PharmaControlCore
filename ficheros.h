/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#ifndef FICHEROS_H
#define FICHEROS_H
#endif

#include "typedef.h"
#include <time.h>

//Función que realiza la lectura de un fichero que contiene los nombres de los ficheros con información de los medicamentos
int leeFicheros(char ** fileNames);

//Función que realiza la lectura de un fichero con los datos necesarios de un medicamento
int leeMedicamentos(int horizonte, MEDICINE* med, char * fileName);