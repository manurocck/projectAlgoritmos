
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "reportin.h"

using namespace std;

void agendar(Agenda *nuevaAgenda, Agenda *&dondeGuardar){
	if(!dondeGuardar){
		dondeGuardar = nuevaAgenda;
		dondeGuardar->aDerecha = NULL;
		dondeGuardar->aIzquierda = NULL;
	}
	else{
		if(nuevaAgenda->fecha->fecha <= dondeGuardar->fecha->fecha )
			agendar(nuevaAgenda, dondeGuardar->aIzquierda);
		else
			agendar(nuevaAgenda, dondeGuardar->aDerecha);
	}
	return;
}

void elegirVehiculo(Garage *garage, int pasajeros, int &terminado, char patente[]){
	int k=1, t;
	bool eop;
	Garage *garageux = garage;
	do{
		if(pasajeros <= garageux->estacionado->capacidad){
			system("cls");
			cout<<"      Travel R & A"<<endl
				<<"       NUEVO VIAJE "<<endl
				<<" ======================="<<endl<<endl
				<<" POSIBLE VEHICULO "<<k<<" :"<<endl
				<<"        YEAR  : "<<garageux->estacionado->year<<endl
				<<"       MARCA  : "<<garageux->estacionado->marca<<endl
				<<"      MODELO  : "<<garageux->estacionado->modelo<<endl
				<<"     PATENTE  : ";	for(t=0; t<6; t++){
											if(t==3)
												cout<<" ";
											cout<<garageux->estacionado->patente[t];
										}
	  cout<<endl<<"   CAPACIDAD  : "<<garageux->estacionado->capacidad<<endl<<endl
				<<"                   Space ->siguiente vehiculo"<<endl
				<<"                   Esc   ->elegir OTRO conductor"<<endl<<endl<<endl
				<<"                ---> Enter para ELEGIR vehiculo <---";
			switch(getch() ){
				case 13://{
					for(t=0; t<6; t++){
						patente[t] = garageux->estacionado->patente[t];
					}
					patente[6] = '\0';
					terminado = 10;
					eop = true;
					break;//}
				case 32://{
					k++;
					break;//}
				case 27://{
					eop = true;
					break;//}
				default:;
			}
		}
		garageux = garageux->nextVehicle;
		if(!garageux){
			garageux = garage;
			k=1;
		}
	}
	while(!eop);

	return;
}
void elegirConductor(Drivers* driversList, int &terminado, int contador, int &i, char patente[], int pasajerosNUM, int &dniNUM){
	FILE *disponibles;
	int dniLeido;
	Drivers *driver;

	if( i==contador){
		i=0;
	}
	disponibles = fopen("disponibles.dat", "rb");
	fseek(disponibles, sizeof(int)*i, SEEK_SET);
	fread(&dniLeido, sizeof(int), 1, disponibles);
	fclose(disponibles);

	driver = existenciaConductor(driversList, dniLeido);

	cout<<" POSIBLE CONDUCTOR: "<<driver->info->nombre<<" "<<driver->info->apellido<<endl<<endl
		<<"                   Space ->elegir OTRO conductor"<<endl
		<<"                   Esc   ->cancelar ingreso"<<endl<<endl<<endl
		<<"                ---> Enter para ELEGIR conductor <---";
	switch(getch() ){
		case 13://{
			elegirVehiculo(driver->garage, pasajerosNUM, terminado, patente);
			if(terminado == 10)
				dniNUM = dniLeido;
			break;//}
		case 32://{
			i++;
			break;//}
		case 27://{
			terminado = 9;
			break;//}
		default:;
	}
	return;
}

bool analizarYear(int yearNUM){
	int error;
	if(yearNUM<2017 && yearNUM>2005)
		return true;
	else{
		error = 405;
		checkError(error);
	}
	return false;
}
bool analizarCapacidad(int capacidad){
	int error = 0;
	if(capacidad == 12 || capacidad == 24 || capacidad == 40 || capacidad == 60){
		return true;
	}
	error = 406;
	checkError(error);

	return false;
}

void pedirYear(char year[], int &yearNUM, int &terminado, int &i){
	int k;
	cout<<"  YEAR DE FABRICA : ";
	for(k = 0; k<i ; k++){
		cout<<year[k];
	}
	if(i<4){
		switch( year[i] = getch() ){
			case 27:
				terminado = 9;
				break;
			case 8:
				if(i>0)
					i--;
				break;
			default:
				if(numero(year[i]) )
					i++;
				break;
		}
	}
	else if(i==4){
		cout<<endl<<"                    Enter ->continuar";
		switch(getch() ){
			case 27:
				terminado = 9;
				break;
			case 8:
				if(i>0)
					i--;
				break;
			case 13:
				yearNUM = palabraAnumero(year, 5);
				if(analizarYear(yearNUM) )
					terminado = 3;
				i=0;
				break;
			default:;
		}
	}
 	return;
}
void pedirCapacidad(char capacidad[], int &capacidadNUM, int &terminado, int &i){
	int k, error=0;
	cout<<" CAPACIDAD : ";
	for(k=0; k<i; k++){
		cout<<capacidad[k];
	}
	if(i<2){
		switch( (capacidad[k] = getch() ) ){
			case 13:
				if(i==0){
					error = 406;
					checkError(error);
				}
				else{
					capacidad[i] = capacidad[i-1];
					capacidad[i-1] = '0';
					i++;
				}
				break;
			case 27:
				terminado = 9;
				break;
			case 8:
				if(i>0)
					i--;
				break;
			default:
				i++;
				break;
		}
	}
	else{ //confirma capacidad
		cout<<endl<<"                       Enter ->confirmar";
		switch(getch()){
			case 8:
				i--;
				break;
			case 27:
				terminado = 9;
				break;
			default:
				capacidadNUM = palabraAnumero(capacidad, 3);
				if(analizarCapacidad(capacidadNUM) ){
					terminado = 4;
				}
				i=0;
				break;
		}
	}

	return;
}

bool guardoVehiculo(Garage *&garage, int dniNG, int &error, char nombre[], char apellido []){ // falta hacer ints en chars
	Garage *garageux;
	Vehicle *autaux;
	int terminado = 1, i = 0, k = 0, l;
	char patente[6], marca[20], modelo[20], year[4], capacidad[2];
	bool listo, eop;
	int yearNUM, capacidadNUM;

	do{
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"  VEHICULO de "<<nombre<<" "<<apellido<<endl
			<<" ======================= Esc ->salir"<<endl<<endl;
		switch(terminado){
			case 1:        //{ INGRESAR PATENTE
				cout<<"  PATENTE : ";
					for(k=0; k<i; k++){
						cout<<patente[k];
					}
				if(i<6){
					patente[i] = getch();
					switch(patente[i]){
						case 13:
							error = 404;
							break;
						case 27:
							terminado = 9;
							break;
						case 8:
							if(i>0)
								i--;
							break;
						default:
							i++;
					}
				}
				else if(i==6){
					cout<<endl<<"                  Enter ->continuar";
					switch(getch() ){
						case 27:
							terminado = 9;
							break;
						case 8:
							i--;
							break;
						case 13:
							if( analizarIngreso(patente, 2, error) ){
								terminado = 2;
								patente[6] = '\0';
							}
							else{
								error = 404;
								checkError(error);
							}
							i = 0;
						default:;
					}
				}
				break;//}
			case 2:       //{ AÑO DE FABRICACION
				pedirYear(year, yearNUM, terminado, i);
				break;//}
			case 3:      //{ CAPACIDAD
				pedirCapacidad(capacidad, capacidadNUM, terminado, i);
				break; //}
			case 4:     //{ MARCA
				cout<<" MARCA: ";
				for(k=0; k<i; k++){
					cout<<marca[k];
				}
				if(i<20	 && !listo){
					marca[i] = getch();
					switch(marca[i]){
						case 13:
							marca[i] = '\0';
							listo = true;
							break;
						case 27:
							terminado = 9;
							break;
						case 8:
							if(i>0)
								i--;
							break;
						case 32:
							if(i == 0 || marca[i-1] == 32)
								break;
						default:
							i++;
					}
				}
				else{
					i = 0;
					if (analizarIngreso(marca, 3, error) ){
						terminado = 5;
					}
					checkError(error);
					listo = false;
				}
				break;//}
			case 5:    //{ MODELO
				cout<<" MODELO: ";
				for(k=0; k<i; k++){
					cout<<modelo[k];
				}
				if(i<20 && !listo){
					modelo[i] = getch();
					switch(modelo[i]){
						case 13:
							modelo[i] = '\0';
							listo = true;
							terminado = 10;
							break;
						case 27:
							terminado = 9;
							break;
						case 8:
							if(i>0)
								i--;
							break;
						case 32:
							if(i == 0 || modelo[i-1] == 32)
								break;
						default:
							i++;
					}
				}
				else{
					i = 0;
					listo = false;
					if (analizarIngreso(modelo, 3, error) ){
						terminado = 10;
					}
					checkError(error);
				}
				break;//}
			case 9:   //{ CERRAR SUBPROGRAMA, SIN CARGAR
				eop = true;
				break;//}
			case 10: //{ CERRAR SUBPROGRAMA, CARGAR VEHICULO EXITOSAMENTE
				cout<<"CONFIRME LOS SIGUIENTES DATOS: "<<endl
					<<"        YEAR  : "<<yearNUM<<endl
					<<"       MARCA  : "<<marca<<endl
					<<"      MODELO  : "<<modelo<<endl
					<<"     PATENTE  : "; for(l=0; l<6; l++){ //mostrar patente con un espacio
											if(l==3)
												cout<<" ";
											cout<<patente[l];
										}
		        cout<<endl
					<<"   CAPACIDAD  : "<<capacidadNUM<<endl<<endl<<endl
					<<"               Enter ->CONFIRMAR "<<endl
					<<"               Esc   ->CANCELAR"<<endl;
				switch(getch() ){
					case 13: //{ ENTER
						if(!garage){
							garageux = new Garage();
							garage = garageux;
						}
						else{
							garageux = garage;
							while(garageux->nextVehicle){
								garageux = garageux->nextVehicle;
							}
							garageux->nextVehicle = new Garage();
							garageux = garageux->nextVehicle;
						}
						garageux->nextVehicle = NULL;
						//listo el garage
						garageux->estacionado = new Vehicle();
							autaux = garageux->estacionado;
							autaux->dni = dniNG;
							autaux->year = yearNUM;
							autaux->capacidad = capacidadNUM;
							for(i=0 ; i<7 ; i++){
							autaux->patente[i] = patente[i];
							}
							for(i=0 ; i<20 ; i++){
							autaux->marca[i] = marca[i];
							autaux->modelo[i] = modelo[i];
							}
						eop = true;
						return true;
						break;//}
					case 27: //{ ESCAPE
						eop = true;
						break;//}
					default:;
				}
			break;//}
		}
	}
	while(!eop);

    return false;
}
bool guardoConductor(Drivers *&driversList, int dniNG, int &error){
	Drivers *driveraux;
	InfoDriver *infoD;
	int contrato, k, i=0, terminado = 1;
	char nombre[50], apellido[50];
	do{
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"     NUEVO CONDUCTOR "<<endl
			<<" ======================= Esc ->salir"<<endl<<endl;
		switch(terminado){
			case 1://{ NOMBRE
				if(i<50){
					cout<<"   NOMBRE : ";
					for(k=0; k<i; k++){
						cout<<nombre[k];
					}
					switch( (nombre[i] = getch()) ){
						case 13:
							nombre[i] = '\0';
							i=50;
							break;
						case 27:
							terminado = 9;
							break;
						case 8:
							if(i>0)
								i--;
							break;
						case 32:
							if(i == 0 || nombre[i-1] == 32)
								break;
						default:
							if(i==49){
								cout<<nombre[i];
								getch();
							}
							i++;
							break;
					}
				}
				else if(i==50){
					if (analizarIngreso(nombre, 4, error) ){
						terminado = 2;
						i=0;
					}
					else
						terminado = 9;
				}
				break;//}
			case 2://{ APELLIDO
				if(i<50){
					cout<<"  APELLIDO: ";
					for(k=0; k<i; k++){
						cout<<apellido[k];
					}
					switch( (apellido[i] = getch()) ){
						case 13:
							apellido[i] = '\0';
							i=50;
							break;
						case 27:
							terminado = 9;
							break;
						case 8:
							if(i>0)
								i--;
							break;
						case 32:
							if(i == 0 || apellido[i-1] == 32)
								break;
						default:
							if(i==49){
								cout<<apellido[i];
								getch();
							}
							i++;
							break;
					}
				}
				else if(i==50){
					if (analizarIngreso(apellido, 4, error) )
						terminado = 10;
					else
						terminado = 9;
				}
				break;//}
			case 9://{ CERRAR SUBP, CANCELAR INGRESO
				checkError(error);
				terminado = 666;
				break;//}
			case 10://{ CERRAR SUBP, CREAR CONDUCTOR
				if(!driversList){
					driversList = new Drivers();
					driversList->nextDriver = NULL;
					driveraux = driversList;
					contrato = 1000;
				}
				else{
					driveraux = driversList;
					while(driveraux->nextDriver){
						driveraux = driveraux->nextDriver;
					}
					contrato = driveraux->info->contrato;
					contrato++;
					driveraux->nextDriver = new Drivers();
					driveraux = driveraux->nextDriver;
				}

				infoD = new InfoDriver();
				infoD->contrato = contrato;
				infoD->dni = dniNG;
				k=-1;
				do{
					k++;
					infoD->nombre[k] = nombre[k];
				}while(nombre[k] != '\0' || k<49);
				k=-1;
				do{
					k++;
					infoD->apellido[k] = apellido[k];
				}while(apellido[k] != '\0' || k<49);


				driveraux->info = infoD;
				driveraux->agenda = NULL;
				driveraux->garage = NULL;
				driveraux->nextDriver = NULL;

				return true;
				//}
		}
	}
	while(terminado != 666);
	return false;
}
bool guardoViaje(int fechaNUM, int dniNUM, int destinoNUM, int horaNUM, int pasajerosNUM, char patente[], Drivers *driversList){
	Viaje *nuevoViaje;
	Agenda *nuevaAgenda;
	Drivers *driver;

	nuevoViaje = new Viaje();
	nuevoViaje->fecha = fechaNUM;
	nuevoViaje->dni = dniNUM;
	nuevoViaje->total = (pasajerosNUM * costoPasaje(destinoNUM));
	nuevoViaje->destino = destinoNUM;
	nuevoViaje->hora = horaNUM;
	for(int i=0; i<7; i++)
		nuevoViaje->patente[i] = patente[i];

	nuevaAgenda = new Agenda();
	nuevaAgenda->fecha = nuevoViaje;

	driver = existenciaConductor(driversList, dniNUM);
	agendar(nuevaAgenda, driver->agenda);

	return true;
}

void analizarDisponibilidadVehiculo(Garage *garage, int minimosPasajeros, bool &disponible){
	do{
		if(minimosPasajeros <= garage->estacionado->capacidad){
			disponible = true;
			return;
		}
		garage = garage->nextVehicle;
	}while(garage);
	disponible = false;
	return;
}
void analizarDisponibilidadFecha(int fecha, Agenda *agenda, bool &disponible){
	if(fecha < (agenda->fecha->fecha) ){
		if(agenda->aIzquierda)
			analizarDisponibilidadFecha(fecha, agenda->aIzquierda, disponible);
	}
	else if( (fecha > agenda->fecha->fecha) ){
		if(agenda->aDerecha)
			analizarDisponibilidadFecha(fecha, agenda->aDerecha, disponible);
	}
	else if(disponible){
		if(fecha == agenda->fecha->fecha || fecha == (agenda->fecha->fecha-1) || fecha == (agenda->fecha->fecha+1) ){
			disponible = false;
		}
	}
	return;
}

void analizarFecha(int fechaNUM, int date, int &terminado, int &i){
	int fechaAUX, estado = 0, error = 0;
	bool biciesto;

	biciesto = false; //AAAAMMDD

	if(fechaNUM<=date || fechaNUM > (date+200000) ){
		error = 800;
	}

	fechaAUX = fechaNUM/10000; //(año)
	if( (fechaAUX%4) == 0 ){
		if(fechaAUX%1000)
			biciesto = true;
	}

	fechaAUX = fechaNUM/100;
	fechaAUX = fechaAUX%100; //(mes)
	if(fechaAUX<1 || fechaAUX>12){
		error = 801;
	}
	else{
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
	}
	if(biciesto && (estado == 28))
		estado += 1;

	fechaAUX = fechaNUM%100;
	if(fechaAUX>estado || fechaAUX<1){
		error = 802;
	}

	if(error){
		checkError(error);
		terminado = 1;
		i=0;
	}
	else{
		i=0;
		terminado = 3;
	}

	return;
}
void analizarPasajeros(char pasajeros[], int &pasajerosNUM, int &terminado ){
	int error = 0;
	pasajerosNUM = palabraAnumero(pasajeros, 3);
	if(numero(pasajeros[0]) && numero(pasajeros[1]) ){
		if(pasajerosNUM < 61 && pasajerosNUM>0){
			terminado = 5;
		}
		else{
			error = 1100;
		}
	}
	else{
		error = 1100;
	}
	if(error){
		terminado = 3;
		checkError(error);
	}
	return;
}
void analizarHora(char horaP[], int &horaNUM, int &terminado, int &i){
	horaNUM = palabraAnumero(horaP, 5);
	int hora = horaNUM/100;
	int minutos = horaNUM%100;
	int error = 0;

	if(hora>23 || hora<0){
		error = 900;
	}
	if(minutos>59 || minutos<0){
		error = 901;
	}
	if(error){
		checkError(error);
	}
	else
		terminado = 8;

	i=0;
    return;
}

void conductoresDisponibles(int fechaNUM, int pasajerosNUM, Drivers* driversList, int &contador, int &terminado, int &i){
	FILE *disponibles;
	bool disponible = true;
	int error;
	do{
		if(driversList->agenda){
			analizarDisponibilidadFecha(fechaNUM, driversList->agenda, disponible);
		}
		if(disponible && driversList->garage){ //auto con capacidad necesaria
			analizarDisponibilidadVehiculo(driversList->garage, pasajerosNUM, disponible);
		}else{
			disponible = false;
		}

		if(disponible){ //si esta disponible, guardalo en archivo
			if(!contador){
				disponibles = fopen("disponibles.dat", "wb");
				fwrite(&(driversList->info->dni), sizeof(int), 1, disponibles);
				fclose(disponibles);
			}
			else{
				disponibles = fopen("disponibles.dat", "ab");
				fwrite(&(driversList->info->dni), sizeof(int), 1, disponibles);
				fclose(disponibles);
			}
			contador+=1;
		}

		disponible = true;
		driversList = driversList->nextDriver;
	}
	while(driversList);
	if(!contador){
		error = 1000;
		checkError(error);
		terminado = 1;
		i=0;
	}
	else{
		cout<<" HAY "<<contador;
		if(contador==1)
			cout<<" CONDUCTOR DISPONIBLE ";
		else
			cout<<" CONDUCTORES DISPONIBLES ";

		cout<<"EL DIA DE LA FECHA"
			<<endl<<endl<<"                                               Enter ->continuar";
		i=0;
		terminado = 6;
		getch();
	}

	return;
}

void mostrarIngresado(char palabra[], int i){
	int k;
	for(k=0; k<i;k++){
		cout<<palabra[k];
		if(k==1 || k==3)
			cout<<" / ";
	}
	if(i!=6){
		if(i<2){ //ingreso dia
			cout<<endl<<"                dia : ";
			for(k=0; k<i;k++){
				cout<<palabra[k];
			}
		}
		else if(i<4){ //mes
			cout<<endl<<"                      mes :";
			for(k=2; k<i;k++){
				cout<<palabra[k];
			}
		}
		else if(i<6){ // año
			cout<<endl<<"                            year : 20";
			for(k=4; k<i;k++){
				cout<<palabra[k];
			}
		}
	}
	return;
}

void pedirFecha(char fecha[], int &i, int &terminado){
	mostrarIngresado(fecha, i);
	if(i!=6){
		switch( (fecha[i] = getch() ) ){
			case 13:
				if( (i%2) ){
					fecha[i] = fecha[i-1];
					fecha[i-1] = '0';
					i++;
				}
				break;
			case 27:
				terminado = 9;
				break;
			case 8:
				if(i>0)
					i--;
				break;
			default:
				i++;
				break;
		}
	}
	else{ //confirma fecha
		fecha[6] = '\0';
		cout<<endl<<"                                      Enter ->confirmar";

		switch(getch()){
			case 8:
				i = 5;
				break;
			case 27:
				terminado = 9;
				break;
			case 13:
				terminado = 2;
				i=0;
				break;
			default:;
		}
	}
	return;
}
void pedirPasajeros(char pasajeros[], int &terminado, int &i){
	int k, error=0;
	cout<<" NUMERO DE PASAJEROS : ";
	for(k=0; k<i; k++){
		cout<<pasajeros[k];
	}
	if(i<2){
		switch( (pasajeros[k] = getch() ) ){
			case 13:
				if(i==0){
					error = 1100;
					checkError(error);
				}
				else{
					pasajeros[i] = pasajeros[i-1];
					pasajeros[i-1] = '0';
					i++;
				}
				break;
			case 27:
				terminado = 9;
				break;
			case 8:
				if(i>0)
					i--;
				break;
			default:
				i++;
				break;
		}
	}
	else{ //confirma pasajeros
		cout<<endl<<"                       Enter ->confirmar";
		switch(getch()){
			case 8:
				i--;
				break;
			case 27:
				terminado = 9;
				break;
			case 13:
				terminado = 4;
				i=0;
				break;
			default:;
		}
	}
}
void pedirDestino(char destino[], int &destinoNUM, int &terminado, int &i){
	cout<<"  L I S T A  DE  D E S T I N O S "<<endl<<endl
		<<" 1-> Mar Del Plata"<<endl
		<<" 2-> Necochea"<<endl
		<<" 3-> Pinamar"<<endl
		<<" 4-> Villa Gesell"<<endl
		<<" 5-> San Bernardo"<<endl
		<<" 6-> Mendoza"<<endl
		<<" 7-> Bariloche"<<endl<<endl<<endl
		<<"                      SU ELECCION : ";
	if(i==0){
		switch( (destino[i] = getch() ) ){
			case 27:
				terminado = 9;
			default:
				if(numero(destino[i]) && destino[i]< '8'){
					destinoNUM = palabraAnumero(destino, 4);
					i++;
				}
				break;
		}
	}
	if(i==1){
		cout<<destino<<endl
			<<"                                     Enter ->confirmar";
		switch( getch() ){
			case 27:
				terminado = 9;
				break;
			case 8:
				i--;
				break;
			case 13:
				i=0;
				terminado = 7;
				break;
			default:;
		}
	}
	return;
}
void pedirHora(char hora[], int &horaNUM, int &terminado, int&i){
	int k;
	cout<<"   (formato 24hs)"
		<<"   HORA DE SALIDA:  ";

	for(k=0 ; k<i ; k++){
		cout<<" "<<hora[k];
		if(k==1)
			cout<<" : ";
	}
	if(i<4){
		if(i!=3){
			for(k=k ; k<4 ; k++){
				cout<<" _ ";
				if(k==1)
					cout<<" : ";
			}
		}
		switch( hora[i] = getch() ){
			case 13:
				if(i==1){
					hora[i] = hora[i-1];
					hora[i-1] = '0';
					i++;
				}
				break;
			case 27:
				terminado = 9;
				break;
			case 8:
				if(i>0)
					i--;
				break;
			default:
				if (numero(hora[i]) )
					i++;
				break;
		}
	}
	if(i==4){
		cout<<" "<<hora[3]<<endl
			<<"                                  Enter ->confirmar";
		switch( getch() ){
			case 27:
				terminado = 9;
				break;
			case 8:
				i--;
				break;
			case 13:
				analizarHora(hora, horaNUM, terminado, i);
				break;
			default:;
		}
	}

	return;
}

void ingresarViaje(Drivers *driversList, int &error, int date){
	bool eop;
	int terminado=1, contador=0, i=0;
	char fecha[6], pasajeros[2], destino[2], patente[7], hora[4];
	int fechaNUM, pasajerosNUM, destinoNUM, horaNUM, dniNUM;

	if(!driversList)
		error = 1000;
	else{
		do{
			system("cls");
			cout<<"      Travel R & A"<<endl
				<<"       NUEVO VIAJE "<<endl
				<<" ======================= Esc ->cancelar"<<endl<<endl;
			switch(terminado){
				case 1://{ Pedir fecha
					cout<<" FECHA DE SALIDA ";
					pedirFecha(fecha, i, terminado);
					break;//}
				case 2://{ Analiza fecha
					analizarFecha( (fechaNUM=palabraAnumero(fecha,2)), date, terminado, i);
					break;//}
				case 3://{ Pedir pasajeros
					pedirPasajeros(pasajeros, terminado, i);
					break;//}
				case 4://{ Analizar pasajeros
					analizarPasajeros( pasajeros, pasajerosNUM, terminado );
					break;//}
				case 5://{ Analizar disponibilidad y guardar disponibles en "disponibles.dat"
					conductoresDisponibles(fechaNUM, pasajerosNUM, driversList, contador, terminado, i);
					break;//}
				case 6://{ Pedir destino
					pedirDestino(destino, destinoNUM, terminado, i);
					break;//}
				case 7://{ Pedir hora
					pedirHora(hora, horaNUM, terminado, i);
					break;//}
				case 8://{ Elegir chofer
					elegirConductor(driversList, terminado, contador, i, patente, pasajerosNUM, dniNUM);
					break;//}
				case 9://{ Cerrar subp, sin guardar
					cout<<"     INGRESO DE VIAJE"<<endl
						<<"     C A N C E L A D O";
					eop = true;
					break;//}
				case 10://{ Cerrar subp, guardar datos
					if(guardoViaje(fechaNUM, dniNUM, destinoNUM, horaNUM, pasajerosNUM, patente, driversList)){
						eop = true;
						cout<<"       VIAJE INGRESADO"<<endl
							<<"  C O R R E C T A M E N T E";
					}
					else
						terminado = 9;

					break;//}
			}
		}while(!eop);
	}
	cout<<endl<<endl<<"                   Enter ->continuar";
	getch();
	return;
}
void ingresarVehiculo(Drivers *driversList, int &error){
	bool eop, ingresoDni;
	char dni[8];
	int i=0, k, dniNUM;
	Drivers *driveraux;

	do{
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"      NUEVO VEHICULO "<<endl
			<<" ======================= Esc ->salir"<<endl<<endl;
		if(!ingresoDni){
			cout<<" D N I del propietario : ";
			for (k=0; k<i; k++)
				cout<< dni[k];
			if(i<8){
				switch(dni[i] = getch() ){
					case 13:
						if(i==7){ //un dni viejo
							dni[i]='\0';
							i++;
						}
						else
							error = 402;
						break;
					case 27:
						eop = true;
						break;
					case 8:
						if(i>0)
							i--;
						break;
					default:
						i++;
						break;
				}
			}
			else if(i == 8){ //termina de ingresar dni
				cout<<endl
					<<"                         Enter ->continuar";
				switch(getch()){
					case 8:
						i--;
						break;
					case 27:
						eop = true;
						break;
					case 13:
						if(analizarIngreso(dni, 1, error) ){
							dniNUM = palabraAnumero(dni,1);
							if( (driveraux = existenciaConductor(driversList, dniNUM) ) ){
								ingresoDni = true;
							}
							else{
								error = 403;
							}
						}
						else{
							error = 402;
						}
						i = 0;
						checkError(error);
					default:
						break;
				}
			}
		}
		else{
			if( guardoVehiculo(driveraux->garage, dniNUM, error, driveraux->info->nombre, driveraux->info->apellido) )
				cout
					<<"   VEHICULO INGRESADO"<<endl
					<<" E X I T O S A M E N T E";
			else
				cout
					<<"  INGRESO DE VEHICULO"<<endl
					<<"   C A N C E L A D O";
			getch();
			eop = true;
		}
	}
	while(!eop);
	return;
}
void ingresarConductor(Drivers *&driversList, int &error){
	char dni[8];
	int i=0, k, dniNUM;
	bool eop, ingresoDni;

	do{
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"     NUEVO CONDUCTOR "<<endl
			<<" ======================= Esc ->salir"<<endl<<endl;
		cout<<" D N I : ";
		for (k=0; k<i; k++)
			cout<< dni[k];
		if(!ingresoDni){
			if(i<8){
				dni[i] = getch();
				switch(dni[i]){
					case 13:
						if(i==7){ //un dni viejo
							dni[i]='\0';
							i++;
						}
						else
							error = 402;
						break;
					case 27:
						eop = true;
						break;
					case 8:
						if(i>0)
							i--;
						break;
					default:
						i++;
						break;
				}
			}
			else if(i == 8){ //termina de ingresar dni
				cout<<endl
					<<"                       Enter ->continuar";
				switch(getch()){
					case 8:
						i--;
						break;
					case 27:
						eop = true;
						break;
					case 13:
						if(analizarIngreso(dni, 1, error) ){
							dniNUM = palabraAnumero(dni,1);
							if( ( existenciaConductor(driversList, dniNUM) ) ){
								i = 0;
								error = 700;
							}
							else{
								ingresoDni = true;
							}
						}
						else{
							error = 402;
							i=0;
						}
						checkError(error);
					break;
					default:;
				}
			}
		}
		else{
			if(guardoConductor(driversList, dniNUM, error)){
				cout<<endl
					<<"    CONDUCTOR INGRESADO"<<endl
					<<" C O R R E C T A M E N T E ";
			}
			else{
				cout<<endl
					<<"   INGRESO DE CONDUCTOR"<<endl
					<<"     C A N C E L A D O     ";
			}
			cout<<endl<<"                        Enter ->continuar";
			eop = true;
			getch();
		}
	}
	while(!eop);
	return;
}

void cargarDatosManuales(Drivers *driversList, int date){
	bool eop;
	int error = 0;
	do{
		menu(3,date);
		switch(getch()){
			case '1':
				ingresarVehiculo(driversList, error);
				break;
			case '2':
				ingresarConductor(driversList, error);
				break;
			case '3':
				ingresarViaje(driversList, error, date);
				break;
			case 27:
				eop = true;
				break;
			default:
				break;
		}
		if (error){
			checkError(error);
		}
	}while(!eop);
	return;
}
//reportes
void calcularTotal(Agenda *agenda, int date, int &total, int &contador){
	if(agenda->aIzquierda){
		calcularTotal(agenda->aIzquierda, date, total, contador);
	}
	if( ( (agenda->fecha->fecha)/100) == (date/100) ){
		total += ( (agenda->fecha->total*4)/10);
		contador++;
	}
	if(agenda->aDerecha){
		calcularTotal(agenda->aDerecha, date, total, contador);
	}
}

void totalDelMes(Drivers *driver, int date, int fecha){
	int totalNUM=0, contador = 0;
	bool ok;

	system("cls");
	cout<<"      Travel R & A"<<endl
		<<"   CONTRATO : "<<driver->info->contrato<<endl
		<<" =======================  "<<date%100<<"/"<<(date/100)%100<<"/"<<date/10000<<endl<<endl;
	if(driver->agenda){
		calcularTotal(driver->agenda, fecha, totalNUM, contador);
		if(contador)
			cout<<"        TOTAL A PAGAR : $"<<totalNUM<<endl<<endl
				<<"  POR UN TOTAL DE "<<contador<<" VIAJES"<<endl;
		else
			cout<<"  ESTE CONDUCTOR NO REALIZO"<<endl
				<<" NI REALIZARA VIAJES ESTE MES"<<endl;
	}
	else{
		cout<<" ESTE CONDUCTOR NO TIENE"<<endl
			<<" VIAJES PROGRAMADOS"<<endl;
	}
	cout<<"                                  Enter ->continuar";
	do{
		switch(getch() ){
			case 13:
			case 27:
				ok = true;
			default:
			    break;
		}
	}while(!ok);

	return;
}
void totalEspecifico(Drivers *driver, int date){
	bool listo, eop;
	char fecha[8];
	int k, i=0, fechaNUM;

	fecha[7] = '1';
	fecha[6] = '0';
	do{
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"   REPORTE : "<<driver->info->contrato<<endl
			<<" =======================  "<<date%100<<"/"<<(date/100)%100<<"/"<<date/10000<<endl<<endl;
		if(i<4){
			cout<<"PEDIR REPORTE DEL YEAR : ";
			for(k = 0; k<i; k++){
				cout<<fecha[k];
			}
			switch( (fecha[i] = getch() ) ){
				case 27:
					eop = true;
					break;
				case 8:
					if(i>0)
						i--;
					break;
				default:
					if(numero(fecha[i]) )
						i++;
			}
		}
		else if (i>3 && i<6){
			cout<<"                  YEAR : ";
			for(k=0; k<4; k++){
				cout<<fecha[k];
			}cout<<endl<<" PEDIR REPORTE DEL MES : ";
			for(k=4; k<i ; k++){
				cout<<fecha[k];
			}
			switch( (fecha[i] = getch() ) ){
				case 27:
					eop = true;
					break;
				case 8:
					i--;
					break;
				default:
					if(numero(fecha[i]) )
						i++;
			}
		}
		else{ //confirmar
			fechaNUM = palabraAnumero(fecha, 6);
			cout<<"                  YEAR : "<<fechaNUM/10000<<
			endl<<"                   MES : "<<(fechaNUM/100)%100<<
			endl<<"                        Enter ->confirmar";
			switch( getch() ){
				case 27:
					eop = true;
					break;
				case 8:
					i--;
					break;
				case 13:
					listo=true;
					break;
				default:;
			}
		}
	}
	while(!listo && !eop);
	if(listo){
		totalDelMes(driver, date, fechaNUM);
	}

	return;
}

void menuReportes(Drivers *driversList, int date){
	bool ok, eop;
	Drivers *driveraux = driversList;
	do{
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"  REPORTE CONDUCTOR : "<<driveraux->info->apellido<<endl
			<<" =======================  "<<date%100<<"/"<<(date/100)%100<<"/"<<date/10000<<endl<<endl
			<<"   1  . TOTAL DE ESTE MES"<<endl
			<<"    2  . TOTAL DE MES ESPECIFICO"<<endl<<endl<<endl
			<<"                   Enter ->siguiente conductor"<<endl
			<<"                   Esc   ->menu principal";
		ok = false;
		while(!eop && !ok){
			switch(getch() ){
				case '1':
					totalDelMes(driveraux, date, date);
					ok = true;
					break;
				case '2':
					totalEspecifico(driveraux, date);
					break;
				case '3':
					break;
				case 13:
					if(driveraux->nextDriver)
						driveraux = driveraux->nextDriver;
					else
						driveraux = driversList;
					ok = true;
					break;
				case 27:
					eop = true;
					break;
				default:;
            }
		}
	}
	while(!eop);

	return;
}
