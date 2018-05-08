#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <iostream>

struct Viaje{		//| TR
	int fecha;
	int dni;
	int destino;
	int total;
	int hora;
	char patente[7];
};
struct Vehicle{ 	//| UC
	int dni;
	int year;
	int capacidad;
	char patente[7];
	char marca[20];
	char modelo[20];
};
struct InfoDriver{	//| TS
	int dni;
	int contrato;
	char nombre[50];
	char apellido[50];
};
struct Garage{//   LI
	Vehicle *estacionado;
	Garage *nextVehicle;
};
struct Agenda{//     ST
	Viaje *fecha;
	Agenda *aIzquierda;
	Agenda *aDerecha;
};
struct Drivers{//      S
	InfoDriver *info;
	Garage *garage;
	Agenda *agenda;
	Drivers *nextDriver;
};

#endif