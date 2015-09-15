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
#include <unistd.h>
#include <sys/types.h>
#include "typedef.h"
#include "matrices.h"

int esPar(int num);

int main(int argc, char *argv[]){

	int J;
	int Jmin = 1000;
	int i;
	int minDiasPedido;
	int horizonte;
	int error = 0;
	int statval;
	char *argumentos[4];
	argumentos[0] = "./OFH";
	argumentos[3] = NULL;

	if(argc<2){
		printf("ERROR1:\nForma correcta de llamar al programa: 'CalcNumDias {nºdias_horizonte}'\n");
		error = 1;
	}else{
		for(i=0;argv[1][i]!='\0';i++){
			if(argv[1][i]<'0'||argv[1][i]>'9'){
				error=2;
				
			}
		}
		/*Comprobamos que el numero de días en el horizonte tiene un formato correcto*/
		if(error!=0){
			printf("ERROR2:\nValor de numero de dias en el horizonte incorrecto. Introduzca valor numerico\n");
			error = 2;
		}else{
			horizonte=atoi(argv[1]);
			argumentos[1] = argv[1];

			int maxDiasPedido;
			if(esPar(horizonte)==0){
				maxDiasPedido = horizonte/2;
			}else{
				maxDiasPedido = horizonte/2+1;
			}
			printf("Maximo dias de Pedidos->%d\n",maxDiasPedido );

			for(i = 0; i<maxDiasPedido; i++){
				printf("Pasada bucle n#->%d\n",i+1 );
				sprintf(argumentos[2],"%d",i+1);
				if(fork()==0){
					exit(execvp(argumentos[0], argumentos));
				}else{
					wait(&statval);
					if(WIFEXITED(statval)){
						J = WEXITSTATUS(statval);
						printf("J_%d\t%d\n",i+1, J);
						if(J<Jmin&&J>0){
							minDiasPedido = i+1;
							Jmin = J;
						}
					}else{
						printf("ERROR3: Proceso no terminado con salida\n");
						error = 3;
					}
				}
			}
			if(Jmin == 1000){
				printf("ERROR4:\nNo hay solucion minima\n");
				error = 4;
			}else{
				//sprintf(argumentos[2], "%d", minDiasPedido);
				//printf("minDiasPedido=%d\nJmin=%d\n", minDiasPedido,Jmin);
			/*
				if(fork()==0){
					exit(execvp(argumentos[0], argumentos));	
				}else{
					wait(&statval);
					if(WIFEXITED(statval)){
						Jmin = WEXITSTATUS(statval);
						printf("\n\nSolución final\nJmin = %d\nNumero de días de pedido = %s\n", Jmin, argumentos[2]);
						error = Jmin;
					}else{
						printf("ERROR5: Proceso no terminado con salida\n");
						error = 5;
					}
				}*/
			}
		}
	}
	return error;
}

/*
	Funcion que devuelve 0 si num es par y 1 en otro caso.
*/
int esPar(int num){
	return num%2;
}