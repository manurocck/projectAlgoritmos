#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include "variables.h"


bool letra(char caracter);
bool numero(char caracter);
int numeroRelativo(char letra, int pos);
int palabraAnumero(char palabra[], int id);
void menu(int id, int date);
void checkError(int &error);
void cargarDatosDePrueba(Drivers *&conductores, int &date);
bool analizarIngreso(char palabra[], int id, int &error);
Drivers *existenciaConductor(Drivers *driversList, int dniNG);
int costoPasaje(int i);
void definirDestino(int i, int &duracionViaje, char destino[]);

#endif