posibilidades: posibilidades.o evalua.o
	
	gcc	-W  -Wall	-c	fechas.c
	gcc	-W 	-Wall	-c	ficheros.c
	gcc	-W	-Wall	-c	evalua.c
	gcc	-W 	-Wall	-c	matrices.c
	gcc	-W	-Wall	-c	posibilidades.c
	gcc -o OFH posibilidades.o evalua.o fechas.o ficheros.o matrices.o
