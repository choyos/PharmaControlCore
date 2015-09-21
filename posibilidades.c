/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#include "evalua.h"
#include "ficheros.h"
#include "fechas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "typedef.h"
#include "matrices.h"
#include "funciones.h"


#define LUNES 0
#define MARTES 1
#define MIERCOLES 2
#define JUEVES 3
#define VIERNES 4
#define SABADO 5
#define DOMINGO 6
#define TAM_FILE_NAME 20


int main(int argc, char *argv[]){
	printf("\n");
	clock_t start = clock();  
	
    
	/*Inicialización de variables para la ejecución del programa*/
	int horizonte;	//Dias en el horizonte
	int j;		//Auxiliar para recorrido de matrices
	int i=0;	//Auxiliar para recorrido de matrices
	int k;		//Auxiliar para recalculo de matrices
	int n;		//Auxiliar para recalculo y traspaso de matrices
	int limite=1;	//Limite para el calculo del tope de posibilidades
	int error=0;	//Variable de error

	//Variables para el trabajo con la lista de medicamentos
	MEDICINE * listaMeds = NULL;	//Lista para mantener la información de los medicamentos
	MEDICINE * medNueva = NULL;	//Puntero util para crear nuevos nodos de la lista
	MEDICINE medAux;	//Estructura auxiliar para almacenar la información de los medicamentos

	//Variable para trabajar con cada posibilidad de pedido
	int * posibilidad;

	//Variables para trabajo con las posibilidades de pedido
	int numPedidos;
	int numDiasNo=argc-3;
	int diasMes;
	int aux=0;

	//Variables para el cálculo de los costos y seguimiento de información
	float Jtotal;
	float * Jmin;
	float Jtotalmin;
	int ** matStockOptimo;
	int ** matPedidosOptimos;
	int primeraVez = 0;

	//Variable para el trabajo con los nombres de los ficheros de datos
	char ** filesName = NULL;

	//Variable para el conteo del número de medicamentos
	int numMed = 0;

	
	/*Comprobamos que el numero de argumentos recibidos es el correto*/
	if (argc<3){	
		error=-1;
		printf("ERROR1:\nNumero de argumentos de la funcion incorrectos\n");
		printf("La llamada a la funcion debe ser \"%s\" \"numero de dias en el horizonte\" \"numero de pedidos en el horizonte\" \"OPCIONAL:fecha de dias de no pedido\":\n",argv[0]);
		printf("dd/mm/aaaa\n");
	}else{
		for(i=0;argv[1][i]!='\0';i++){
			if(argv[1][i]<'0'||argv[1][i]>'9'){
				error=-2;
			}
		}
		/*Comprobamos que el numero de días en el horizonte tiene un formato correcto*/
		if(error!=0){
			printf("ERROR2:\nValor de numero de dias en el horizonte incorrecto. Introduzca valor numerico\n");
		}else{
			
			horizonte=atoi(argv[1]);
			for(i=0;argv[2][i]!='\0';i++){
				if(argv[2][i]<'0'||argv[2][i]>'9'){
					error=-3;
				}
			}
			/*Comprobamos que el numero de dias de pedido tiene un formato correcto*/
			if(error!=0){
				printf("ERROR3:\nValor de numero de pedidos en el horizonte incorrecto. Introduzca valor numerico\n");
			}else{
						
				numPedidos=atoi(argv[2]);
				/*Comprobamos que el numero de días de pedido no sea mayor que el numero de dias posible*/
				if(numPedidos>horizonte){
					error=-4;
					printf("ERROR4:\nNumero de dias de pedido mayor que dias en el horizonte\n");
				}else{
				//Inicializar vector diasNO
						int diasNO[horizonte];
						for(i=0;i<horizonte;i++){
							diasNO[i]=0;
						}
					
					/*Comprobamos que se han introducido fechas sin error:*/
					if(argc>3){
						
						int *FechaActual;
						inicializaVector(3, &FechaActual);

						fechaHoy(FechaActual);
						//Fecha introducida por linea de comandos
						k=0;
/*----------------------Inicializamos la matriz de fechas para trabajar---------
------------------------más comodamente con ellas al ser enteros--------------*/
						char auxFecha[5];
						int ** Fecha;
						inicializaMatriz(numDiasNo, 3, &Fecha);
						//Realizamos un bucle para recorrer todas las fechas introducidas
						//por la línea de comandos
						for(n=0;n<numDiasNo;n++){	
							j=0;						
							k=0;	
							//Y otro para ir separando día, mes y año de la fecha
							//para facilitar el trabajo con las mismas
							for(i=0;argv[n+3][i]!='\0';i++){
								if(argv[n+3][i]=='/'){
									auxFecha[k]='\0';
									Fecha[n][j]=atoi(auxFecha);
									j++;
									k=0;
								}else if(argv[n+3][i]<'0'||argv[n+3][i]>'9'){
									error=-5;
								}else{
									auxFecha[k]=argv[n+3][i];
									k++;
								}
							}
							auxFecha[k]='\0';
							Fecha[n][j]=atoi(auxFecha);
						}
/*----------------------Comprobamos si las fechas están en el horizonte pedido---*/							
						for(n=0;n<numDiasNo;n++){
							if(Fecha[n][1]>12||Fecha[n][1]<1){
								error=-6;
							}else if(Fecha[n][0]<1){
								error=-6;
							}switch (Fecha[n][1]){
								case 1:
									diasMes = 31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								case 2:
									if(bisiesto(Fecha[n][2])==1){
										diasMes=29;
										if(Fecha[n][0]>29){
											error=-6;
										}
									}
									else{
										diasMes=28;
										if(Fecha[n][0]>28){
											error=-6;
										}
									}
									break;
								case 3:
									diasMes=31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								case 4:
									diasMes=30;
									if(Fecha[n][0]>30){
										error=-6;
									}
									break;
								case 5:
									diasMes=31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								case 6:
									diasMes=30;
									if(Fecha[n][0]>30){
										error=-6;
									}
									break;
								case 7:
									diasMes=31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								case 8:
									diasMes=31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								case 9:
									diasMes=30;
									if(Fecha[n][0]>30){
										error=-6;
									}
									break;
								case 10:
									diasMes=31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								case 11:
									diasMes=30;
									if(Fecha[n][0]>30){
										error=-6;
									}
									break;
								case 12:
									diasMes=31;
									if(Fecha[n][0]>31){
										error=-6;
									}
									break;
								default:
									error=-6;
							}
							//Si el año es menor que el actual
							if(FechaActual[2]>Fecha[n][2]){ 
								error=-6;					//error
								liberaVector(FechaActual);
							}else{
								aux=Fecha[n][2]-FechaActual[2];	
								//si la diferencia de años es mayor que uno
								if(aux>1){	
									//error: estará fuera del horizonte
									error=-6;
									liberaVector(FechaActual);
								}else{
									//si el mes es pasado al actual
									if(FechaActual[1]>Fecha[n][1]){ 
										error=-6;			//error
									}else{		//otro caso
										//Distinto año
										if (aux==1){ 
										//	printf("Distinto año\n");
											if(!((Fecha[n][1]==1)&&(FechaActual[1]==12))){ //no es enero y diciembre
												error=-6;		//error
											}else{ //Si lo son
												if(aux==1){ //Si son de meses diferentes
													if(FechaActual[0]+horizonte-diasMes<Fecha[n][0]){//Fuera del horizonte
														error=-6; //error
													}else{
														aux=diasMes-FechaActual[0];
														aux=aux+Fecha[n][0];
														diasNO[aux]=1;
													}
												}
											}
												
										}else{
											aux=Fecha[n][1]-FechaActual[1];
											if(aux>1){
												error=-1;
											}else{ 
												if(aux==1){ //Si son de meses diferentes
													if(FechaActual[0]+horizonte-diasMes-1<Fecha[n][0]){//Fuera del horizonte
														error=-6; //error
													}else{
															aux=diasMes-FechaActual[0];
															aux=aux+Fecha[n][0];
															diasNO[aux]=1;
													}
													
												}else{//CASO del mismo mes
													if(FechaActual[0]>Fecha[n][0]){//Fecha antigua
														error=-6;
													}else if(FechaActual[0]+horizonte-1<Fecha[n][0]){//Fecha fuera del horizonte
														error=-6;
													}else{
														aux=Fecha[n][0]-FechaActual[0];
														diasNO[aux]=1;
													}
												}
											}
										}
									}
								}
							}
						}
						liberaVector(FechaActual);
						liberaMatriz(numDiasNo, Fecha);
					}
					/*Comprobamos si es error sintactico*/
					if (error==-5){
						printf("Error=%d\n",error);
						printf("ERROR5:\nFechas introducidas incorrectos. Utilizar la siguiente notacion:\n");
						printf("dd/mm/yyyy\n");
					/*Comprobamos si la fecha está dentro de fechas posibles*/
					}else if(error==-6){
						printf("ERROR6:\nFecha incorrecta, fuera del horizonte\n");
					}else{

						/*Obtención de la información relativa a los medicamentos*/
						/*Lectura del fichero con los nombres de los ficheros con 
						información de los medicamentos*/
						FILE *fpd;
						//Nombre del fichero en el que vienen los nombres del resto de ficheros
						char * mainFile = "ficheros.pha";

						fpd = fopen ( mainFile , "r" );
						if(fpd == NULL){	//Caso de no apertura pasar el error 
							error = -7;
						}else{
							//Lectura del fichero hasta que termine
							//Reservamos memoria para la matriz
							filesName = (char **) malloc(sizeof(*filesName));

							//Leemos hasta el final del fichero
							while(!feof(fpd)){
								//En cada pasada realizamos reserva dinamica de memoria para la nueva cadena
								filesName = realloc(filesName, (numMed+1) * sizeof(*filesName));
							    filesName[numMed] = malloc(TAM_FILE_NAME * sizeof(char*));

								fscanf(fpd, "%s", filesName[numMed]); //Cada linea la almacenamos en un vector de cadenas de caracteres
								numMed++;
							}
							if( fclose(fpd) ){
								error = -7;
							}
						}
						if(error == -7){
							printf("ERROR 7:\nLectura del fichero para acceder a información de medicamentos no válida\n");
						}else{

							/* Realizamos ahora la lectura de la información de cada uno de los 
							medicamentos de su correspondiente archivo*/
							for(i = 0; i<numMed; i++){
								/*
									Se realizan las operaciones pertinentes
									de apertura, lectura y cerrado de fichero
									con el que intercambiar información con
									el programa en php para la web.
									Se almacenan los datos en la estructura 
									del medicamento.
								*/
								if(leeMedicamentos(horizonte, &medAux, filesName[i]) == -1){
									printf("ERROR 8:\nLectura del fichero %s no válida\n", filesName[i]);
									error = -8;
									break;
								}
								medNueva = CreaNodoMed( medAux.stock, medAux.precio_med, medAux.precio_alm, medAux.coste_pedido, medAux.coste_recogida, medAux.coste_sin_stock, medAux.coste_oportunidad, medAux.repartidos, medAux.maxStock, medAux.minStock, medAux.nTamPedidos, medAux.vTamPedidos, horizonte);
								BorraMedicina(&medAux);
								EnlazaMedicinas (medNueva, &listaMeds);
							}
						
							//Generamos las matrices de posibilidades para todos los fármacos	
							MatrizCombMedicinas(&listaMeds, numPedidos);

							//Posibilidad de mostrar por pantalla toda la información de todos los fármacos
						//	ImprimeMedicinas(listaMeds, horizonte, numPedidos);

	/*--------------------------------------------------------------------------
	------------------------Calculamos posibilidad a posibilidad----------------
	--------------------------------------------------------------------------*/
							for(j=0;j<horizonte;j++){
								limite=limite*2;
							}
							
							inicializaVector(horizonte, &posibilidad);
							int num;
							int noCumple;

							for(num = 0; num<limite; num++){
								//Inicializamos noCumple a 0 para cada posibilidad//
								noCumple = 0;

								convIntToBin(num, horizonte, posibilidad);

								//Comprueba que cumple dias no posibles//
								for(i = 0; i<horizonte; i++){
									if(diasNO[i] == 1 && posibilidad[i] == 1){
										noCumple = 1;
									}
								}
								//Comprueba pedidos consecutivos//
								if(noCumple == 0){
									for(i = 1; i<horizonte; i++){
										if(posibilidad[i] == 1 && posibilidad[i-1] == 1){
											noCumple = 1;
										}
									}
									//Comprueba número de pedidos solicitados//
									if(noCumple == 0){
										int auxNumPedidos = 0;
										for(i = 0; i<horizonte; i++){
											if(posibilidad[i] == 1){
												auxNumPedidos++;
											}
										}
										if(auxNumPedidos != numPedidos){
											noCumple = 1;
										}
										//Apertura de fichero y trabajo para evaluar función de coste
										if(noCumple == 0){

											int flag = 0;

											if(primeraVez == 0){
												primeraVez = 1;
												inicializaMatriz(numMed, horizonte, &matPedidosOptimos);
												inicializaMatriz(numMed, horizonte, &matStockOptimo);
												Jmin = (float*) malloc(numMed*sizeof(float));
											}

											//Funcion en funciones.c
											/*Realiza el calculo de el vector optimo para cada medicamento y almacena la información util
											en el nodo correspondiente*/

											Jtotal = EvaluaMedicinas(&listaMeds, horizonte, numPedidos, posibilidad, matPedidosOptimos, matStockOptimo, Jmin);
											if (Jtotal < Jtotalmin || flag == 0){
												flag = 1;
												Jtotalmin = Jtotal;
												AlmacenaOptimos(&listaMeds, horizonte, matPedidosOptimos, matStockOptimo, Jmin);
											}
										}
									}
								}
							}
							liberaVector(posibilidad);
							liberaMatriz(numMed, matPedidosOptimos);
							liberaMatriz(numMed, matStockOptimo);
						}

						// Liberamos espacios de memoria utilizados durante el proceso
						for(i = 0; i<numMed; i++){
							free(filesName[i]);
							filesName[i] = NULL;
						}
						free(filesName);
						filesName = NULL;
						free(Jmin);
						Jmin = NULL;
						
						ImprimeResultados(&listaMeds, horizonte);
						BorraMedicinas (&listaMeds);
					}
				}
			}
		}
	}
	printf("\n");
	printf("Tiempo transcurrido: %f\n\n", ((double)clock() - start) / CLOCKS_PER_SEC);	
	

	return error;
}