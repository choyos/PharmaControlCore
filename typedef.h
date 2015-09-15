/*  Proyecto fin de carrera*/
/* Optimizacion del stock de farmacos en hospitales*/
/* Fecha: 2014-2015*/
/*Apellidos: Hoyos Martín
Nombre: César*/

#ifndef TYPEDEF_H
#define TYPEDEF_H

/* Estructura para el manejo de información que está ligada
a cada uno de los medicamentos. Esta estructura incorpora campos para la
información que va ligada a cada medicamento y un puntero al siguiente medicamento del mismo laboratorio.*/
typedef struct NODEMEDICINE{
	int stock;		/*Stock actual*/
	float precio_med;		/*Precio de compra del medicamento*/
	float precio_alm;		/*Precio de almacenamiento del medicamento*/
	float coste_pedido;		/*Coste de realizar un pedido*/
	float coste_recogida;	/*Coste de recibir un pedido*/
	float coste_sin_stock;	/*Coste por quedarse sin stock*/
	float coste_oportunidad;/*Coste por tener en stock*/
	int* repartidos; 	/*Estimacion de repartidos*/
	int maxStock;		/*Stock maximo almacenable*/
	int minStock;		/*Stock minimo para que no haya desabastecimiento*/
	int nTamPedidos;	/*Numero de posibilidades de pedidos*/
	int* vTamPedidos;	/*Diferentes posibilidades de pedidos*/
}MEDICINE;

/* Estructura para el manejo de información ligada a cada una los laboratorios. 
Esta estructura incorpora una tabla con el nombre del laboratorio,
y dos punteros: al siguiente laboratorio, con la finalidad de montar una lista util para manejar mejor la informacion;y al primer medicamento de este laboratorio, con la finalidad de completar así el arbol con toda la informacion necesaria.*/
typedef struct NODELAB{
	char * lab;		/*Nombre del laboratorio*/
	char * code_lab;	/*Codigo del laboratorio*/	
	int minOrder;		/*Pedido minimo a realizar*/
	int priceOrder;		/*Valor del pedido que se haria con los deficit actuales*/
	int* historicalOrders;	/*Tabla con los valores historicos de los pedidos realizados*/
	struct NODELAB * sig;
	struct NODEMEDICINE * firstmedicine;
}LABORATORY;

#endif
