#ifndef REPORTIN_H_INCLUDED
#define REPORTIN_H_INCLUDED

#include <iostream>
#include "variables.h"

void agendar(Agenda *nuevaAgenda, Agenda *&dondeGuardar);
void elegirVehiculo(Garage *garage, int pasajeros, int &terminado, char patente[]);
void elegirConductor(Drivers* driversList, int &terminado, int contador, int &i, char patente[], int pasajerosNUM, int &dniNUM);

bool analizarYear(int yearNUM);
bool analizarCapacidad(int capacidad);

void pedirYear(char year[], int &yearNUM, int &terminado, int &i);
void pedirCapacidad(char capacidad[], int &capacidadNUM, int &terminado, int &i);

bool guardoVehiculo(Garage *&garage, int dniNG, int &error, char nombre[], char apellido []);
bool guardoConductor(Drivers *&driversList, int dniNG, int &error);bool guardoViaje(int fechaNUM, int dniNUM, int destinoNUM, int horaNUM, int pasajerosNUM, char patente[], Drivers *driversList);

void analizarDisponibilidadVehiculo(Garage *garage, int minimosPasajeros, bool &disponible);
void analizarDisponibilidadFecha(int fecha, Agenda *agenda, bool &disponible);

void analizarFecha(int fechaNUM, int date, int &terminado, int &i);
void analizarPasajeros(char pasajeros[], int &pasajerosNUM, int &terminado );
void analizarHora(char horaP[], int &horaNUM, int &terminado, int &i);

void conductoresDisponibles(int fechaNUM, int pasajerosNUM, Drivers* driversList, int &contador, int &terminado, int &i);

void mostrarIngresado(char palabra[], int i);
void pedirFecha(char fecha[], int &i, int &terminado);
void pedirPasajeros(char pasajeros[], int &terminado, int &i);
void pedirDestino(char destino[], int &destinoNUM, int &terminado, int &i);
void pedirHora(char hora[], int &horaNUM, int &terminado, int&i);

void ingresarViaje(Drivers *driversList, int &error, int date);
void ingresarVehiculo(Drivers *driversList, int &error);
void ingresarConductor(Drivers *&driversList, int &error);

void cargarDatosManuales(Drivers *driversList, int date);
//reportes
void calcularTotal(Agenda *agenda, int date, int &total, int &contador);

void totalDelMes(Drivers *driver, int date, int fecha);
void totalEspecifico(Drivers *driver, int date);

void menuReportes(Drivers *driversList, int date);

#endif