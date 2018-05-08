
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "variables.h"

using namespace std;

void estacionar(Garage *nuevoGarage, Garage *&garage){     //guarda auto en garage
	Garage *aux = garage;

	if(!garage){ //primer auto cargado a dicho garage
		garage = nuevoGarage;
		garage->nextVehicle = NULL;
	}
	else{
		while(aux->nextVehicle){
			aux = aux->nextVehicle;
		}
		aux->nextVehicle = nuevoGarage;
		aux = aux->nextVehicle;
		aux->nextVehicle = NULL;
	}
	return;
}
void loadVehicles(Drivers *driversList, int &error, bool prueba){
	FILE *autoData;
	Vehicle *autaux;
	Drivers *driveraux;
	Garage *garageux;
	bool listo;

	if(driversList){
        if(prueba)
            autoData = fopen("PRUEBAgarageEmpresa.dat","rb");
        else
            autoData = fopen("garageEmpresa.dat","rb");
		if(autoData){
			autaux = new Vehicle();
			fread(autaux, sizeof(Vehicle), 1, autoData);
			while(!feof(autoData) ){
				garageux = new Garage();
				garageux->estacionado = autaux;
				garageux->nextVehicle = NULL;
				driveraux = driversList;
				while(driversList && !listo){
					if(driversList->info->dni == autaux->dni){
						estacionar(garageux, driversList->garage);
						listo = true;
					}
					else
						driversList = driversList->nextDriver;
				}
				driversList = driveraux;
				listo = false;
				autaux = new Vehicle();
				fread(autaux, sizeof(Vehicle), 1, autoData);
			}
			delete autaux;
		}
		fclose(autoData);
	}

	return;
}
void loadDriverInfo(Drivers *&driversList, int &error, bool prueba){
	FILE *driversData;
	InfoDriver *infaux;
	Drivers *driveraux;
	bool primero = true;

    if(prueba)
        driversData = fopen("PRUEBAdriverinfo.dat","rb");
    else
        driversData = fopen("driverinfo.dat", "rb");
	if(driversData){
		infaux = new InfoDriver();
		fread(infaux, sizeof(InfoDriver), 1, driversData);
		while(!feof(driversData) ){
			if(primero){
				primero = false;
				driversList = new Drivers();
				driveraux = driversList;
			}
			else{
				while(driveraux->nextDriver){
					driveraux = driveraux->nextDriver;
				}
				driveraux->nextDriver = new Drivers();
				driveraux = driveraux->nextDriver;
			}
			driveraux->nextDriver = NULL;
			driveraux->info = infaux;

			infaux = new InfoDriver();
			fread(infaux, sizeof(InfoDriver), 1, driversData);
		}
		delete infaux;
	}
	fclose(driversData);
}
void loadAgendas(Drivers *driversList, int &error, bool prueba){
	FILE *agenData;
	Viaje *diaux;
	Drivers *driveraux;
	Agenda *agendaux;
	bool ready;

	if(driversList){
		driveraux = driversList;
        if(prueba)
            agenData = fopen("PRUEBAagendas.dat","rb");
        else
            agenData = fopen("agendas.dat","rb");
		if(agenData){
			diaux = new Viaje();
			fread(diaux, sizeof(Viaje), 1, agenData);
			while(!feof(agenData) ){
				while(driveraux && !ready){
					if(driveraux->info->dni == diaux->dni){ //viaje corresp al conductor
						if(!driveraux->agenda){
							driveraux->agenda = new Agenda();
							agendaux = driveraux->agenda;
						}
						else if (diaux->fecha <= agendaux->fecha->fecha){
							agendaux = driveraux->agenda;
							while(agendaux->aIzquierda){
								agendaux = agendaux->aIzquierda;
							}
							agendaux->aIzquierda = new Agenda();
							agendaux = agendaux->aIzquierda;
						}
						else{
							agendaux = driveraux->agenda;
							while(agendaux->aDerecha){
								agendaux = agendaux->aDerecha;
							}
							agendaux->aDerecha = new Agenda();
							agendaux = agendaux->aDerecha;

						}
						agendaux->fecha = diaux;
						agendaux->aDerecha = NULL;
						agendaux->aIzquierda = NULL;
						ready = true;
					}
					else
						driveraux = driveraux->nextDriver;
				}
				ready = false;
				driveraux = driversList;
				diaux = new Viaje();
				fread(diaux, sizeof(Viaje), 1, agenData);
			}
			delete diaux;
		}
		fclose(agenData);

		driversList = driveraux;
	}


	return;
}
void loadDia(int &date, bool prueba){
	FILE *fecha;
	int fechaAUX, estado, plusyear = 0, plusmonth = 0;
	bool biciesto;
    if(!prueba){
        fecha = fopen("dia.dat","rb");
        if(fecha){
            fread(&date, sizeof(int), 1, fecha);
        }
        fclose(fecha);
        date++;
        do{
            date = date + (plusmonth*100) + (plusyear*10000);
            fechaAUX = date/10000; //(año)
            if( (fechaAUX%4) == 0 ){
                if(fechaAUX%1000)
                    biciesto = true;
            }

            fechaAUX = date/100;
            fechaAUX = fechaAUX%100; //(mes)

            if(fechaAUX<7){
                if( (fechaAUX%2) == 0 ){
                    if(fechaAUX == 2)
                        estado = 28;
                    else
                        estado = 30;
                }
                else
                    estado = 31;
            }
            else{
                if( (fechaAUX%2) ){
                    estado = 30;
                }
                else
                    estado = 31;
            }

            if(biciesto && (estado == 28))
                estado += 1;

            fechaAUX = date%100; //(dia)
            if(fechaAUX>estado){ //plusmonth
                plusmonth = 1;
                date-= estado;
            }
            else{
                plusmonth = 0;
            }

            fechaAUX = date/100;
            fechaAUX = fechaAUX%100; //(mes)
            if(fechaAUX>12){ //plusyear
                plusyear = 1;
                date -= 1200;
            }
            else{
                plusyear = 0;
            }

        }
        while(plusmonth || plusyear);
    }
	else
        date = 20161105;
	return;
}
void loadAllData(Drivers *&driversList, int &date, int &error, bool prueba){
	loadDriverInfo(driversList, error, prueba);
	loadVehicles(driversList, error, prueba);
	loadAgendas(driversList, error, prueba);
	loadDia(date, prueba);

	return;
}
void loadDatosDePrueba(Drivers *&conductores, int &date){
	int error = 0;
	bool prueba = true;

	loadAllData(conductores, date, error, prueba);

	return;
}
