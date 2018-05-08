#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include <iostream>
#include "variables.h"

void estacionar(Garage *nuevoGarage, Garage *&garage, bool prueba);
void loadVehicles(Drivers *driversList, int &error, bool prueba);
void loadDriverInfo(Drivers *&driversList, int &error, bool prueba);
void loadAgendas(Drivers *driversList, int &error, bool prueba);
void loadDia(int &date, bool prueba);
void loadAllData(Drivers *&driversList, int &date, int &error, bool prueba);
void loadDatosDePrueba(Drivers *&conductores, int &date);

#endif
