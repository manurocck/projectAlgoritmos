#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

#include <iostream>
#include "variables.h"

void saveDriverInfo(InfoDriver *info, int &error, bool &primerD);
void saveGarage(Garage *garage, int &error, bool &primerG);
void saveAgenda(Agenda *agenda, int &error, bool &primerA);
void saveAllData(Drivers *driversList, int date, int &error);

#endif