/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#ifndef FECHAS_H
#define FECHAS_H
#endif

#include "typedef.h"
#include <time.h>

//Función que evalua cada posibilidad para devolver un coste total de medicamentos
void compruebaFecha();

//Función que devuelve si un año es o no bisiesto
int bisiesto(int year);

//Funcion que obtiene las fechas de los dias de pedido optimo
void obtieneFechasPedidos(int*v, int tam, int ** FechasPedido);

//Funcion que devuelve la fecha formateada del dia
void fechaPedido(int dia, int * fecha);

//Funcion que recibe un vector y devuelve los campos del mismo rellenos con {día, mes, año} en formato entero.
void fechaHoy(int * fechaActual);