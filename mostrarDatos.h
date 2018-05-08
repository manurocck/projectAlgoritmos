#ifndef MOSTRARDATOS_H_INCLUDED
#define MOSTRARDATOS_H_INCLUDED

#include <iostream>
#include "variables.h"

void mostrarDatosViaje(Viaje *viaje, int &k, Drivers *driversList);
void verInformacionLegal(InfoDriver *driver, int p);
void verGarage(Garage *garage, int p);
void recorrerSalidas(Agenda *viajes, int &k, Drivers* driversList, int date);
void verAgenda(Drivers *driver, Drivers *driversList, int date, int i);
void menuConductores(Drivers *driversList, int date);

#endif
