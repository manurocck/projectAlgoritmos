
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "variables.h"

using namespace std;

bool letra(char caracter){// Funcion tomada del trabajo practico, hecho en conjunto
	bool estado;
	if (caracter >= 'A' && caracter <= 'Z')
		estado = true;
	else if (caracter >= 'a' && caracter <= 'z')
		estado = true;
	else
		estado = false;

	return estado;
}
bool numero(char caracter){// Funcion tomada del trabajo practico, hecho en conjunto
	bool estado;
	if(caracter >= '0' && caracter <= '9')
		estado = true;
	else
		estado = false;

	return estado;
}

int numeroRelativo(char letra, int pos){
	int relativo = 0;
	switch(letra){
		case '0':
			break;
		case '1':
			relativo = (1*pos);
			break;
		case '2':
			relativo = (2*pos);
			break;
		case '3':
			relativo = (3*pos);
			break;
		case '4':
			relativo = (4*pos);
			break;
		case '5':
			relativo = (5*pos);
			break;
		case '6':
			relativo = (6*pos);
			break;
		case '7':
			relativo = (7*pos);
			break;
		case '8':
			relativo = (8*pos);
			break;
		case '9':
			relativo = (9*pos);
			break;
		default:;
	}
	return relativo;
}
int palabraAnumero(char palabra[], int id){
	int pos = 1, palabraNum = 0;
	int i;
	switch(id){
		case 1://{ convierte dnis
			if(palabra[7] == '\0')
				pos = 1000000;
			else
				pos = 10000000;
			for(i = 0; i<8; i++){
				if (palabra[i] != '\0'){
					palabraNum += numeroRelativo(palabra[i], pos);
					pos = pos/10;
				}
			}
			break;//}
		case 2://{ convierte fechas del formato ddmmaa al aaaammdd
			for(i=0; i<6; i++){
				if(i==0)
					pos = 10;
				else if(i == 2)
					pos = 1000;
				else if(i == 4)
					pos = 100000;
				palabraNum += numeroRelativo(palabra[i], pos);
				pos = pos/10;
			}
			palabraNum += 20000000;
			break;//}
		case 3://{ convierte pasajeros/capacidad
			pos = 10;
			for(i=0; i<2; i++){
				palabraNum += numeroRelativo(palabra[i], pos);
				pos/=10;
			}
			break;//}
		case 4://{ convierte destino
			palabraNum += numeroRelativo(palabra[0], pos);
			break;//}
		case 5://{ convierte años
			pos = 1000;
			for(i=0; i<4; i++){
				palabraNum += numeroRelativo(palabra[i], pos);
				pos/=10;
			}
			break;//}
		case 6: // convierte fechas del formato aaaamm al aaaammdd
			pos = 10000000;
			for(i=0; i<8; i++){
				palabraNum += numeroRelativo(palabra[i], pos);
				pos = pos/10;
			}
			break;
	}
	return palabraNum;
}

void menu(int id, int date){
	system("cls");
	cout<<"      Travel R & A"<<endl;
	switch(id){
		case 1://{ principia
			cout<<"      MENU PRINCIPAL       hoy es:"<<endl
				<<" =======================  "<<date%100<<"/"<<(date/100)%100<<"/"<<date/10000<<endl<<endl
				<<"  1  . VER CONDUCTORES"<<endl
				<<"   2  . CARGAR DATOS"<<endl
				<<"    3  . REPORTES"<<endl<<endl<<endl
				<<"     Esc   ->guardar & salir";
		break;//}
		case 3://{ carga manual
			cout<<"     CARGA DE DATOS        hoy es:"<<endl
				<<" =======================  "<<date%100<<"/"<<(date/100)%100<<"/"<<date/10000<<endl<<endl
				<<"  1  . NUEVO VEHICULO" <<endl
				<<"   2  .  NUEVO CONDUCTOR" <<endl
				<<"    3  .   NUEVO VIAJE"<<endl<<endl<<endl
				<<"      Esc  ->menu anterior";
		break;//}
		case 9://{ introduccion
			cout<<" I N T R O D U C C I O N "<<endl<<endl
				<<" Para comenzar a usar el programa, puede cargar"<<endl
				<<" los datos de prueba o ingresar manualmente los"<<endl
				<<" datos a utilizar."<<endl<<endl
				<<"              presione 'A' para cargar datos de prueba"<<endl
				<<"                    o  'B' para ingresar un nuevo conductor"<<endl<<endl<<endl
				<<"                                       Esc  ->salir del programa";
			break;//}
	}
	return;
}
void checkError(int &error){
	if (error){
		system("cls");
		cout<<"      Travel R & A"<<endl
			<<"        ERROR "<<error<<endl
			<<" ======================="<<endl<<endl;
		switch(error){
			case 401://{ conductores
				cout<<" NO SE ENCONTRARON DATOS"<<endl
					<<"  DE CONDUCTORES EN EL"<<endl
					<<"        PROGRAMA"<<endl<<endl
					<<" Intenta cargar los datos de prueba o "<<endl
					<<" ingreselos manualmente"<<endl;
				break;//}
			case 402://{ dni
				cout<<" EL DNI INGRESADO DEBE SER"<<endl
					<<"  VALIDO Y DEBE CONTENER"<<endl
					<<"       SOLO NUMEROS"<<endl<<endl
					<<" Intenta ingresar el dni de la siguiente "<<endl
					<<" forma: ' 20892102 ' "<<endl;
				break;//}
			case 403://{ dni-conductor
				cout<<"  NO HAY REGISTRO DE ALGUN"<<endl
					<<" CONDUCTOR CON EL DNI INGRESADO"<<endl;
				break;//}
			case 404://{ patente
				cout<<"     PATENTE INCORRECTA"<<endl<<endl
					<<" El formato debe ser: "<<endl
					<<"      ' ABC123 ' o ' 123ABC '"<<endl
					<<"        (patente Argentina)"<<endl;
				break;//}
			case 405://{ año de fabr
				cout<<"   SOLO ACEPTAMOS AUTOS DE"<<endl
					<<"         NUEVA GAMMA "<<endl
					<<"   (modelos posteriores al 2006)"<<endl;
				break;//}
			case 406://{ capacity
				cout<<" LA CAPACIDAD DEL VEHICULO"<<endl
					<<"   DEBE SER DE: "<<endl
					<<"        12, 24, 40 o 60 plazas"<<endl;
				break;//}
			case 407://{ SOLO LETRAS
				cout<<"  DATO INGRESADO INCORRECTO"<<endl
					<<"    EL DATO DEBE CONTENER"<<endl
					<<"         SOLO LETRAS"<<endl<<endl
					<<" En caso de ser un numero, registrarlo en letras"<<endl
					<<" De ser el numero 9, ingresar: nueve"<<endl;
				break;//}
			case 700://{ existe conduct
				cout<<"     EL DNI INGRESADO "<<endl
					<<"    COINCIDE CON EL DE "<<endl
					<<"       UN CONDUCTOR "<<endl<<endl
					<<"  Intente ingresar un dni distinto"<<endl
					<<"  o el que quizo ingresar, pero correctamente."<<endl;
				break;//}
			case 800://{ año
				cout<<"   LA FECHA SOLICITADA "<<endl
					<<"  DEBE ESTAR COMPRENDIDA "<<endl
					<<"   ENTRE LA FECHA ACTUAL "<<endl
					<<"   Y 20 YEARS POSTERIORES"<<endl<<endl
					<<"  Intente corregir la fecha ingresada."<<endl;
				break;//}
			case 801://{ mes
				cout<<"   LA FECHA SOLICITADA "<<endl
					<<"        NO EXISTE "<<endl<<endl
					<<"  Intente corregir el mes de la fecha"<<endl
					<<"  ingresada. Debe ser un numero entre (1 y 12).";
				break;//}
			case 802://{ dia
				cout<<"   LA FECHA SOLICITADA "<<endl
					<<"        NO EXISTE "<<endl<<endl
					<<"  Intente corregir el dia de la fecha."<<endl
					<<"  Chequee el mes que eligio para el viaje"<<endl
					<<"  y que el dia sea una fecha posible.";
				break;//}
			case 900://{ hora
				cout<<"     HORA INCORRECTA "<<endl<<endl
					<<"  Intente la corregir la hora."<<endl
					<<"  Debe estar en el formato de 24 horas."<<endl
					<<"  Las 6 p.m son las 18:00hs y las 6 a.m, las 6:00 hs";
				break;//}
			case 901://{ minutos
				cout<<"     HORA INCORRECTA "<<endl<<endl
					<<"  Intente la corregir los minutos."<<endl
					<<"  Debe estar en el formato sexagesimal."<<endl
					<<"  Los minutos deben estar entre 0 y 59."<<endl
					<<"  En caso de ser 60, incrementar la hora.";
				break;//}
			case 1000://{ fecha ocupada
				cout<<"     NO SE PUEDE CONCRETAR EL INGRESO"<<endl
					<<"                 DEL VIAJE. "<<endl
					<<"      TODOS LOS CONDUCTORES VIAJAN EL "<<endl
					<<"  DIA DE LA FECHA O NO TIENEN LOS VEHICULOS "<<endl
					<<"      NECESARIOS PARA REALIZAR EL VIAJE "<<endl<<endl
					<<" Debera contratar un conductor, cambiar la fecha del viaje"<<endl
					<<" o mismo, cambiar el numero de pasajeros";
				break;//}
			case 1100://{ pasajeros
				cout<<"     INGRESO INCORRECTO "<<endl
					<<"  LA CANTIDAD DE PASAJEROS "<<endl
					<<"     DEBE SER MENOR A 60"<<endl<<endl
					<<"  Chequee haber ingresado el valor correctamente";
				break;//}
			default:
				return;
		}
		cout<<endl<<endl<<"                    Enter ->continuar";
        do{
            switch(getch() ){
                case 13:
                case 27:
                    error = 0;
                break;
            }
        }while(error);
	}
	return;
}

bool analizarIngreso(char palabra[], int id, int &error){ // id 1:dni  2:patente  3:marca
	int k = 0;
	switch(id){
		case 1:    //{ dni
			for (k=0 ; k<8 ; k++){
				if (numero(palabra[k]) ){
					k++;
				}
				else{
					if(k==7 && palabra[k] == '\0' ) //dnis de 7 digitos
						return true;
					else
						return false;
				}
			}
			break;//}
		case 2:   //{ patente
			if(letra(palabra[0]) && letra(palabra[1]) && letra(palabra[2]) ){
				if (!numero(palabra[3]) || !numero(palabra[4]) || !numero(palabra[5]) )
					return false;
			}
			else if(letra(palabra[3]) && letra(palabra[4]) && letra(palabra[5]) ){
				if (!numero(palabra[0]) || !numero(palabra[1]) || !numero(palabra[2]) )
					return false;
			}
			else
				return false;
			break;//}
		case 3:  //{ marca
			if (palabra[0] != '\0'){
				while( palabra[k]!= '\0' && !error && k<20 ){
					if(!letra(palabra[k])){
						if(palabra[k] == 32){
							k++;
						}
						else{
							error = 407;
							return false;
						}
					}
					else{
						k++;
					}
				}
			}
			else{
				error = 407;
				return false;
			}
			break;//}
		case 4: //{ nombre y apellido
			if (palabra[0] != '\0' ){
				while( palabra[k]!= '\0' && !error && k<50 ){
					if(!letra(palabra[k]) ){
						if(palabra[k] == 32){
							k++;
						}
						else{
							error = 407;
							return false;
						}
					}
					else{
						k++;
					}
				}
			}
			else{
				error = 407;
				return false;
			}
			break;//}
	}
	return true;
}
Drivers *existenciaConductor(Drivers *driversList, int dniNG){ //si hay algun conductor con el dni ingresado
	while(driversList){
		if(driversList->info->dni == dniNG)
			return driversList;
		else
			driversList = driversList->nextDriver;
	}
	return NULL;
}

int costoPasaje(int i){
	int costoPasaje=0;
	switch(i){
		case 1://{ MDQ
			costoPasaje = 1000;
		break;//}
		case 2://{ NECOCHEA
			costoPasaje = 600;
			break;//}
		case 3://{ PINAMAR
			costoPasaje = 1200;
			break;//}
		case 4://{ VILLA GESELL
			costoPasaje = 900;
			break;//}
		case 5://{ SAN BERNARDO
			costoPasaje = 800;
			break;//}
		case 6://{ MENDOZA
			costoPasaje = 1000;
			break;//}
		case 7://{ BARILOCHE
			costoPasaje = 1700;
			break;//}
	}
	return costoPasaje;
}
void definirDestino(int i, int &duracionViaje, char destino[]){
	switch(i){
		case 1://{ MDQ
			destino[0]='M';
			destino[1]='a';
			destino[2]='r';
			destino[3]=' ';
			destino[4]='D';
			destino[5]='e';
			destino[6]='l';
			destino[7]=' ';
			destino[8]='P';
			destino[9]='l';
			destino[10]='a';
			destino[11]='t';
			destino[12]='a';
			destino[13]='\0';
			duracionViaje=700;
		break;//}
		case 2://{ NECOCHEA
			destino[0]='N';
			destino[1]='e';
			destino[2]='c';
			destino[3]='o';
			destino[4]='c';
			destino[5]='h';
			destino[6]='e';
			destino[7]='a';
			destino[8]='\0';
			duracionViaje = 500;
			break;//}
		case 3://{ PINAMAR
			destino[0]='P';
			destino[1]='i';
			destino[2]='n';
			destino[3]='a';
			destino[4]='m';
			destino[5]='a';
			destino[6]='r';
			destino[7]='\0';
			duracionViaje = 700;
			break;//}
		case 4://{ VILLA GESELL
			destino[0]='V';
			destino[1]='i';
			destino[2]='l';
			destino[3]='l';
			destino[4]='a';
			destino[5]=' ';
			destino[6]='G';
			destino[7]='e';
			destino[8]='s';
			destino[9]='e';
			destino[10]='l';
			destino[11]='l';
			destino[12]='\0';
			duracionViaje = 600;
			break;//}
		case 5://{ SAN BERNARDO
			destino[0]='S';
			destino[1]='a';
			destino[2]='n';
			destino[3]=' ';
			destino[4]='B';
			destino[5]='e';
			destino[6]='r';
			destino[7]='n';
			destino[8]='a';
			destino[9]='r';
			destino[10]='d';
			destino[11]='o';
			destino[12]='\0';
			duracionViaje = 500;
			break;//}
		case 6://{ MENDOZA
			destino[0]='M';
			destino[1]='e';
			destino[2]='n';
			destino[3]='d';
			destino[4]='o';
			destino[5]='z';
			destino[6]='a';
			destino[7]='\0';
			duracionViaje = 1400;
			break;//}
		case 7://{ BARILOCHE
			destino[0]='B';
			destino[1]='a';
			destino[2]='r';
			destino[3]='i';
			destino[4]='l';
			destino[5]='o';
			destino[6]='c';
			destino[7]='h';
			destino[8]='e';
			destino[9]='\0';
			duracionViaje = 1800;
			break;//}
	}
	return;
}
