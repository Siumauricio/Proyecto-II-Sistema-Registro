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


void debugPrint ();
void loadData ();

struct Records {
	char codigo[7];
	char nombre[45];
	char nombreHijos[25];
	int uv;
	int cantHijos;
}Estructura1[15];


int main () {
	Archivo a;
	//loadData ();
	//debugPrint ();
	//a.CrearPlanEstudio ();
   //a.LeerPlanEstudio ();
	for(int i = 0; i < 2; i++) {
		//a.ClasesDisponibles ();
	}
	//a.modificarNota ("CCC107",89);
	int Hijos (0);
	//cout<<a.LCP104 ("CCC105");
	a.modificarNota ("FIL101",77);
	//a.modificarNota()
	a.historialAcademico ();
	cout << "-------------" << endl;
		a.ClasesDisponibles ();


	//loadData (); 
	//debugPrint ();
}

void debugPrint () {
	for(int i = 0; i < 14; i++) {
		cout << "Codigo: " << Estructura1[i].codigo << endl;
		cout << "Nombre:" << Estructura1[i].nombre << endl;
		cout << "UV:" << Estructura1[i].uv << endl;
		cout << "Clases: " << Estructura1[i].nombreHijos << endl;
		cout << "N Hijos: " << Estructura1[i].cantHijos << endl;
		cout << "-------------------------" << endl;
	}
}

void loadData () {
	Archivo a;
	int i = 0;
	ifstream in ("I-01.txt");
	string cadena;
	smatch match;
	smatch match2;
	smatch match3;
	smatch match4;
	while(!in.eof ()) {

		if(!in.is_open ()) {
			cerr << "File can't be opened! " << endl;
			return;
		}
		getline (in,cadena);
		istringstream entrada (cadena);
		if(cadena.find ("Nombre") != std::string::npos) {
			string line (cadena);
			regex re ("Nombre=(.*)-");
			if(regex_search (line,match,re)) {
				string nombre = match[1];
				strcpy (Estructura1[i].nombre,nombre.c_str());
			}
		}
		istringstream entrada2 (cadena);
		if(cadena.find ("Codigo") != std::string::npos) {
			string line (cadena);
			regex re ("Codigo=(.*)'");
			if(regex_search (line,match2,re)) {
				string codigo = match2[1];
				strcpy (Estructura1[i].codigo,codigo.c_str ());
			}
		}
		istringstream entrada3 (cadena);
		if(cadena.find ("UV") != std::string::npos) {
			string line (cadena);
			regex re ("UV=(.*),");
			if(regex_search (line,match3,re)) {
				string UV = match3[1];
				Estructura1[i].uv=atoi (UV.c_str ());
			}
		}
		istringstream entrada4 (cadena);
		if(cadena.find ("Clases") != std::string::npos) {
			string line (cadena);
			regex re ("Clases=(.*)");
			if(regex_search (line,match4,re)) {
				string hijos = match4[1];
				strcpy(Estructura1[i].nombreHijos,hijos.c_str());
				Estructura1[i].cantHijos=a.cantidadHijos (hijos);
			}
		}
		i++;
	}



}