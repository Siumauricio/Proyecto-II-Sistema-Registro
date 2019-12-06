#include <iostream>
#include <string>
#include "PlanEstudio.h"
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <regex>
#include <sstream> 
#include "Archivo.h"
#include <vector>
#include "Estudiante.h"
#include <cstdio>
using namespace std;

int main () {
	Archivo a;
	PlanEstudio nuevo;
	a.Menu ();
	//a.MatricularClases ("MAT103","GEOMETRIA Y TRIGONOMETRIA",4);
	
	/*
	 MAT102, Nombre: ALGEBRA}
	 MAT101, Nombre: INTRODUCCION AL ALGEBRA}
	 Materia { codigo: MAT109, Nombre: CALCULO I}
	MAT103,
	 Materia { codigo: CCC104, Nombre: PROGRAMACION I}
	 Materia { codigo: CCC107, Nombre: INTRODUCCION A LA COMPUTACION}
	nuevo.agregar ("MAT101","INTRODUCCION AL ALGEBRA",4," ");
	nuevo.agregar ("MAT102","ALGEBRA",4,"MAT101");
	nuevo.agregar ("CCC107","INTRODUCCION A LA COMPUTACION",4,"MAT101");
	nuevo.agregar ("CCC104","PROGRAMACION I",4,"CCC107");
	nuevo.agregar ("LCP104","LAB. PROGRA. I",4,"CCC107");
	nuevo.agregar ("CCC105","PROGRAMACION II",4,"CCC104");
	nuevo.agregar ("LCP105","LAB. PROGRA. II",4,"CCC104");
	nuevo.agregar ("CCC105","PROGRAMACION II",4,"LCP104");
	nuevo.agregar ("LCP105","LAB. PROGRA. II",4,"LCP104");
	nuevo.agregar ("MAT103","TRIGO",4,"MAT102");
	nuevo.agregar ("MAT210","CALCULO",4,"MAT102");
	nuevo.agregar ("EIE1","ELECTIVA IDIOMA EXTRANJERO I",4,"");
	nuevo.agregar ("EIE2","ELECTIVA IDIOMA EXTRANJERO II",4,"EIE1");
	nuevo.agregar ("EIE3","ELECTIVA IDIOMA EXTRANJERO III",4,"EIE2");
	nuevo.agregar ("SOC101","SOCIOLOGIA",4,"");
	nuevo.agregar ("FIL101","FILOSOFIA",4,"SOC101");
	nuevo.imprimir ();
	*/
	//;
	//cout << endl;
	a.modificarNota ("MAT103",88);
	a.CrearPlanEstudio ();
	cout << "\n\n";
	a.historialAcademico ();

}
