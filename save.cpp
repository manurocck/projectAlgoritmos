#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "utility.h"
#include "variables.h"

using namespace std;

void saveDriverInfo(InfoDriver *info, int &error, bool &primerD){ //"driverinfo.dat"
	FILE *driverData;
	if (primerD){
		driverData = fopen("driverinfo.dat","wb");
		primerD = false;
	}
	else
		driverData = fopen("driverinfo.dat","ab");

	if(driverData){
		fwrite(info, sizeof(InfoDriver), 1, driverData);
		delete info;
	}
	else{
		error = 600;
	}
	fclose(driverData);
	return;
}
void saveGarage(Garage *garage, int &error, bool &primerG){ //"garageEmpresa.dat"
	FILE *garageData;
	Garage *garageux;

	if (primerG){
		garageData = fopen("garageEmpresa.dat","wb");
		primerG = false;
	}
	else
		garageData = fopen("garageEmpresa.dat","ab");
	while(garage){
		if(garageData){
			fwrite(garage->estacionado, sizeof(Vehicle), 1, garageData);
		}
		else{
			error = 600;
		}
		garageux = garage;
		garage = garage->nextVehicle;
		delete garageux;
	}
	fclose(garageData);
	return;
}
void saveAgenda(Agenda *agenda, int &error, bool &primerA){ //"agendas.dat"
	if(agenda->aIzquierda)
		saveAgenda(agenda->aIzquierda, error, primerA);
	if(agenda->aDerecha)
		saveAgenda(agenda->aDerecha, error, primerA);
	if(agenda){
		FILE *data;

		if (primerA){
			data = fopen("agendas.dat","wb");
			primerA = false;
		}
		else
			data = fopen("agendas.dat","ab");

		if(data){
			fwrite(agenda->fecha, sizeof(Viaje), 1, data);
		}
		else{
			error = 600;
		}

		delete agenda;

		fclose(data);
	}
	return;
}

void saveAllData(Drivers *driversList, int date, int &error){
	FILE *fecha;
	Drivers *driveraux = driversList;
	int i = 1;
	bool primerD = true, primerG = true, primerA = true;
	
	if(driversList){
		do{
			system("cls");

			saveDriverInfo(driversList->info, error, primerD);
			if(driversList->garage)
				saveGarage(driversList->garage, error, primerG);
			if(driversList->agenda)
				saveAgenda(driversList->agenda, error, primerA);

			driveraux = driversList;
			driversList = driversList->nextDriver;
			delete driveraux;
			i++;
		}while(driversList && !error);
		driversList = NULL;
		cout<<endl<<"   H A S T A  "<<endl
				  <<"            E L "<<endl
				  <<"               S I G U I E N T E"<<endl
				  <<"                                D I A !";
		getch();
	}

	fecha = fopen("dia.dat", "wb");
	fwrite(&date, sizeof(int), 1, fecha);
	fclose(fecha);

	return;
}
