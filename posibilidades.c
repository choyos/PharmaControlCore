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


#define LUNES 0
#define MARTES 1
#define MIERCOLES 2
#define JUEVES 3
#define VIERNES 4
#define SABADO 5
#define DOMINGO 6

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
	MEDICINE medicine;	//Estructura para mantener la información del medicamento
	//Matriz de posibilidades de pedidos reales
	int g=0;

	//Matriz base de combinaciones
	int exp4=1;
	int ** matrixComb = NULL;

	int * posibilidad;

	int numPedidos;
	int numDiasNo=argc-3;
	int diasMes;
	int aux=0;

	int x;
	float J;
	float Jmin;
	int *stock;
	int *stockOptimo;
	int *vectorOptimo;

	
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
							}else{
								aux=Fecha[n][2]-FechaActual[2];	
								//si la diferencia de años es mayor que uno
								if(aux>1){	
									//error: estará fuera del horizonte
									error=-6;
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
									liberaVector(FechaActual);
									liberaMatriz(numDiasNo, Fecha);
								}
							}
						}
					}
					/*Comprobamos si es error sintactico*/
					if (error==-5){
						printf("Error=%d\n",error);
						printf("ERROR5:\nFechas introducidas incorrectos. Utilizar la siguiente notacion:\n");
						printf("dd/mm/yyyy\n");
					/*Comprobamos si la fecha está dentro de fechas posibles*/
					}else if(error==-6){
						printf("ERROR6:\nFecha incorrecta, fuera del horizonte");
					}else{

/*--------------------------------------------------------------------------
------------------------Calculo de primera matriz---------------------------
--------------------------------------------------------------------------*/
						for(j=0;j<horizonte;j++){
							limite=limite*2;
						}
						

						inicializaVector(horizonte, &posibilidad);
						int num;
						int noCumple;
						int primeraVez = 0;
						int ** matrix;
						//Vectores comunes a todas las iteraciones
						inicializaVector(horizonte, &stockOptimo);
						inicializaVector(horizonte, &vectorOptimo);

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
										/*
												Se realizan las operaciones pertinentes
												de apertura, lectura y cerrado de fichero
												con el que intercambiar información con
												el programa en php para la web.
												Se almacenan los datos en la estructura 
												del medicamento.
										*/
										//Lectura del fichero
										if(ficheros(horizonte, &medicine) == -1){
											printf("ERROR7: Lectura de fichero no realizada\n");
											error = -7;
										}else{
											if(primeraVez == 0){
												primeraVez = 1;
												
												//Obtenemos primero el numero de combinaciones posibles								
												for(i=0;i<numPedidos;i++){
													exp4=exp4*medicine.nTamPedidos;
												}
												
												int divisor = exp4/medicine.nTamPedidos; //Variable auxiliar para acceder al vector de la forma adecuada
												//Matriz de combinaciones
												inicializaMatriz(exp4, numPedidos, &matrixComb);
												
												for(j=0;j<numPedidos;j++){	//Luego por filas
													for(i=0;i<exp4;i++){	//Primero por columnas
														matrixComb[i][j]=medicine.vTamPedidos[(i/divisor)%medicine.nTamPedidos];
													}
													divisor=divisor/medicine.nTamPedidos;	//Disminuimos la auxiliar para acceder a la posicion correcta
												}
											}

											n = 0;
											inicializaMatriz(exp4, horizonte, &matrix);
											
											// Bucles para la obtencion de la matriz definitiva
											for(k=0;k<exp4;k++){		// Accedemos todas las veces de las combinaciones posibles
												for(j=0;j<horizonte;j++){		// En el recorrido
													if(posibilidad[j]==1){	// Si es 1 se cambia por el valor correspondiente
														matrix[n][j]=posibilidad[j]*matrixComb[k][g];
														g++;
														
													}else{	//Si es 0 se deja igual
														matrix[n][j] = posibilidad[j];
													}							
												}
												g=0;	//Al finalizar cada pasada reiniciamos el contador g a 0
												n++;	//Y pasamos a rellenar la siguiente fila
											}

//------------------------------------------Calculo de J------------------------------------------------------//
											// Una vez obtenidas todas las posibles combinaciones
											// para un determinado horizonte, procedemos al cálculo
											// y consiguiente obtención de los días de pedidos
											// útiles para el farmaceútico

											inicializaVector(horizonte, &stock);

											for(x=0; x<n; x++){
												inicializa(stock, horizonte);
												J = evalua(matrix[x], horizonte, 0, stock, &medicine);
											//	printf("\n%d->\tJ = %f\n",x,J);
												if(x==0){
													Jmin = J;
													for(k=0; k<horizonte; k++){
														vectorOptimo[k]=matrix[x][k];
														stockOptimo[k]=stock[k];
													}
												}
												if(J <Jmin){
													Jmin = J;
													for(k=0; k<horizonte; k++){
														vectorOptimo[k]=matrix[x][k];
														stockOptimo[k]=stock[k];
													}
												}
											}
											liberaVector(medicine.vTamPedidos);
											liberaVector(medicine.repartidos);
											liberaVector(stock);
											liberaMatriz(exp4, matrix);
										}
									}
								}
							}
						}
						
						//Mover el bloque para imprimir bien por pantalla/salida estandar
						printf("Jmin= %f\nVector Óptimo de pedido:", Jmin);
						numPedidos = 0;
						for(x=0;x<horizonte; x++){
							printf("%d ",vectorOptimo[x] );
							if(vectorOptimo[x] != 0){
								numPedidos++;
							}
						}
						printf("\nStock del pedido óptimo:");
						for(x=0;x<horizonte; x++){
							printf("%d ",stockOptimo[x] );
						}
						printf("\n");

						//char **FechasOptimas;
						int ** FechasPedido;
						inicializaMatriz(numPedidos, 3, &FechasPedido);
						//A partir de obtener los valores optimos de días de pedidos
						//debemos obtener ahora las fechas con su correspondiente valor
						printf("\n\n");
						printf("===============\n===Resultado===\n===============\n\n");
						obtieneFechasPedidos(vectorOptimo, horizonte, FechasPedido);
						error = Jmin;
						liberaVector(stockOptimo);
						liberaMatriz(numPedidos, FechasPedido);
						liberaVector(vectorOptimo);
						liberaMatriz(exp4, matrixComb);
						liberaVector(posibilidad);
					}
				}
			}
		}
	}
	printf("\n");
	printf("Tiempo transcurrido: %f\n\n", ((double)clock() - start) / CLOCKS_PER_SEC);	
	
	return error;
}