/*  Trabajo fin de curso de programación 2010*/
/*Apellidos: Hoyos Martín
Nombre: César
Login: ceshoymar */

/*Declaración de funciones de tratamiento de la información recibida*/

#ifndef HORA_H
#define HORA_H

#include "typedef.h"


LABORATORY * CreaNodoLab ( char * lab,char * code_lab,int minOrder,int priceOrder,int* historicalOrders);	//Crea un nodo de tipo laboratorio, con la información leida de la trama.

int ExisteLaboratorio ( LABORATORY * laboratorioAnterior, char * lab);	//Comprueba la existencia de la cadena de la última trama leida.

int ComparaMedicinas ( MEDICINE med1, MEDICINE med2);	//Compara dos nodos de tipo medicina, y los ordena según criterio.


MEDICINE * CreaNodoMed ( char* med_name,char* code,int stock,int dosisperpacket,int price,int maxStock,int minStock,char* lab_name,int* historical;);	//Crea un nodo de tipo medicina, con la información leida de la trama.

void EnlazaLaboratoriosOrdenados (LABORATORY * laboratorioActual, LABORATORY ** laboratorioAnterior);	//Crea la lista de laboratorios enlazando, de forma ordenada según algún criterio a seguir

void EnlazaMedicinasOrdenadas (MEDICINE * medicinaNueva, MEDICINE ** medicinaPrimera);	//Crea la lista de medicinas enlazando, de forma ordenada según criterio a fijar.

void BorraMedicina (MEDICINE ** medicinaPrimera); //Borra la lista completa de medicinas liberando la memoria.

void BorraMedicina (MEDICINE **pp);	//Borra un único programa. Esta función se utiliza en la función BorraSolapamientos.

void BorraLaboratorio (LABORATORY ** ppAnterior);	//Borra la lista completa de laboratorios liberando la memoria. Incluye la función BorraMedicinas, para liberar toda la memoria reservada.

void ImprimeMedicinas (PROGRAM * medicinaPrimera);	//Imprime por la salida estándar la lista de medicinas.

void ImprimeLaboratorio (LABORATORY * pAnterior);	//Imprime por la salida estándar la lista de laboratorios, incluidos sus respectivas medicinas.

MEDICINE * BuscaPunteroLab (LABORATORY *pAnterior, char * lab);	//Busca el puntero del laboratorio (anteriormente creado) a la que va ligada la medicina de la trama actual.

#endif
