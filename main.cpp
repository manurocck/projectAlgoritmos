
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "mostrarDatos.h"
#include "save.h"
#include "load.h"
#include "reportin.h"

using namespace std;

int main(){
	Drivers *driversList = NULL;
	int date = 20161105, error = 0, cdp = 0;
	bool eop;
	loadAllData(driversList, date, error, false);
	do{
		if(driversList){
			menu(1, date);
			switch(getch() ){
				case '1':
					menuConductores(driversList, date);
					cdp = 0;
					break;
				case '2':
					cargarDatosManuales(driversList, date);
					cdp = 0;
					break;
				case '3':
					menuReportes(driversList, date);
					break;
				case 27:
					saveAllData(driversList, date, error);
					eop = true;
					break;
				case 'C':;
				case 'c':
					if(cdp == 0)
						cdp++;
					break;
				case 'd':;
				case 'D':
					if(cdp == 1)
						cdp++;
					else
						cdp = 0;
					break;
				case 'p':;
				case 'P':
					if(cdp == 2)
						loadDatosDePrueba(driversList, date);
					cdp = 0;
					break;
				default:
					cdp = 0;
				break;
			}
			checkError(error);
		}
		else{
			menu(9, date);
			switch(getch() ){
				case 'a':;
				case 'A':
					loadDatosDePrueba(driversList, date);
					if(driversList){
						system("cls");
						cout<<endl
						<<"   Programa elaborado en conjunto por: Richard Silva Porras"<<endl
						<<"                                       Manuel Nielsen"<<endl<<endl
						<<"presione una tecla para comenzar la magia";
						getch();
					}
					break;
				case 'b':;
				case 'B':
					ingresarConductor(driversList, error);
					checkError(error);
					break;
				case 27:
					eop=true;
				default:;
			}
		}
	}while(!eop);

	return 0;
}
