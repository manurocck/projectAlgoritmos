
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "variables.h"
#include "mostrarDatos.h"

using namespace std;

void mostrarDatosViaje(Viaje *viaje, int &k, Drivers *driversList){
	// Drivers *driver = existenciaConductor(driversList, viaje->dni);
	int duracionViaje, horasLL, minutosLL, horas, minutos, horasSS, minutosSS, pasaje;
	char destino[15];

	horasSS = (viaje->hora)/100;
	minutosSS = (viaje->hora)%100;
	definirDestino(viaje->destino, duracionViaje, destino);
	pasaje = costoPasaje(viaje->destino);
	horas = duracionViaje/100;
	minutos = duracionViaje%100;

	minutosLL = minutosSS + minutos;
	horasLL = horasSS + horas;

	if(minutosLL>59){
		horasLL += minutosLL/60;
		minutosLL = minutosLL%60;
	}
	if(horasLL>23){
		horasLL = horasLL%24;
	}

	cout<<" FECHA "<<k<<"   ( "<<(viaje->fecha)%100<<" / "<<( (viaje->fecha)/100 )%100<<" / "<<(viaje->fecha)/10000<<" )"<<endl
		<<"           DESTINO    : "<<destino<<endl
		<<"            SALIDA    : ";
	if(horasSS<10)
		cout<<"0";
	cout<<horasSS<<":";

	if(minutosSS<10)
		cout<<"0";
	cout<<minutosSS<<"hs"<<endl
		<<"           LLEGADA    : ";
	if(horasLL<10)
		cout<<"0";
	cout<<horasLL<<":";
	if(minutosLL<10)
		cout<<"0";
	cout<<minutosLL<<"hs"<<endl
		<<"          PASAJEROS   : "<<(viaje->total)/pasaje<<endl
		<<"       COSTO PASAJE   : $"<<pasaje<<endl<<endl;

	return;
}

void verInformacionLegal(InfoDriver *driver, int p){
	system("cls");
	cout<<"      Travel R & A"<<endl
		<<"       CONDUCTOR "<<p<<endl
		<<" ======================="<<endl<<endl
		<<"  NOMBRE  : "<<driver->nombre<<" "<<driver->apellido<<endl
		<<"    DNI   : "<<driver->dni<<endl
		<<" CONTRATO : "<<driver->contrato<<endl<<endl<<endl
		<<"          Enter -> CONTINUAR ";

	getch();
	return;
}
void verGarage(Garage *garage, int p){
	int i = 1;

	system("cls");
	cout<<"      Travel R & A"<<endl
		<<"       CONDUCTOR "<<p<<endl
		<<" ======================="<<endl<<endl;
	if(!garage){
		cout<<"NO POSEE VEHICULOS PROPIOS"<<endl;
	}
	else
		do{
			cout<<" VEHICULO "<<i<<":"<<endl
				<<"        YEAR  : "<<garage->estacionado->year<<endl
				<<"       MARCA  : "<<garage->estacionado->marca<<endl
				<<"      MODELO  : "<<garage->estacionado->modelo<<endl
				<<"     PATENTE  : "; for(int k=0; k<6; k++){ //mostrar patente con un espacio
					if(k==3)
						cout<<" ";
					cout<<garage->estacionado->patente[k];
				}
			cout<<endl<<"   CAPACIDAD  : "<<garage->estacionado->capacidad<<endl<<endl;
			i++;
			// if(i>2 && i%2){
				// switch(getch() ){

				// }
			// }
			garage = garage->nextVehicle;
		}while(garage);
		cout<<endl<<"              Enter ->CONTINUAR ";

		getch();
	return;
}
void recorrerSalidas(Agenda *viajes, int &k, Drivers* driversList, int date){
	if(viajes->aIzquierda){
		recorrerSalidas(viajes->aIzquierda, k, driversList, date);
	}
	if( (viajes->fecha->fecha) > date){
		mostrarDatosViaje(viajes->fecha, k, driversList);
		k++;
	}
	if(viajes->aDerecha){
		recorrerSalidas(viajes->aDerecha, k, driversList, date);
	}

	return;
}
void verAgenda(Drivers *driver, Drivers *driversList, int date, int i){
	bool ok;
	int k=1;
	system("cls");
	cout<<"      Travel R & A"<<endl
		<<"       CONDUCTOR "<<i<<endl
		<<" ======================="<<endl<<endl;
	if(!driver->agenda)
		cout<<" ESTE CONDUCTOR NO TIENE VIAJES ASIGNADOS";
	if(driver->agenda)
		recorrerSalidas(driver->agenda, k, driversList, date);

	cout<<endl<<endl<<"                                        Enter ->continuar ";
	do{
		switch(getch()) {
			case 13:
			case 27:
				ok=true;
				break;
		}
	}while(!ok);
	return;
}

void menuConductores(Drivers *driversList, int date){
	Drivers *driver = driversList;
	bool eop = false, solouno;
	int i=1, error = 0;
	if(driversList){
		if(!driversList->nextDriver){
			solouno=true;
		}
		while (driversList && !eop){
			system("cls");
			cout<<"      Travel R & A"<<endl
				<<"  CONDUCTOR "<<i<<" : "<<driver->info->apellido<<endl
				<<" =======================  "<<date%100<<"/"<<(date/100)%100<<"/"<<date/10000<<endl<<endl
				<<"  1  . INFORMACION LEGAL "<<endl
				<<"   2  . VEHICULOS PROPIOS "<<endl
				<<"    3  . VIAJES PROXIMOS "<<endl<<endl<<endl;
			if(!solouno)
				cout<<"      Enter ->siguiente conductor "<<endl;
			cout<<"      Esc   ->menu principal ";
			switch(getch() ){
				case '1':
					verInformacionLegal(driver->info, i);
					break;
				case '2':
					verGarage(driver->garage, i);
					break;
				case '3':
					verAgenda(driver, driversList, date, i);
					break;
				case 13:
					if(driver->nextDriver){
						driver = driver->nextDriver;
						i++;
					}
					else{
						driver = driversList;
						i = 1;
					}
					break;
				case 27:
					eop = true;
					break;
				default:;
			}
		}
	}
	else
		error = 401;
	if(error){
		checkError(error);
	}

	return;
}
