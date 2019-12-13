#include "Estudiante.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Archivo.h"
#include <dirent.h>
using namespace std;
void Estudiante::ingresarEstudiante () {
	ofstream archivoE ("Estudiante.dat",ios::out | ios::binary);
	if(!archivoE) {
		cout << "Erro De Lectura en archivo";
		return;
	}
	vector<string>carreras = ObtenerCarreras ();
	int posicion = 0;
	EstudianteRegistro nuevo;
	cout << "Ingrese tu numero de cuenta:";
	cin >> nuevo.numeroCuenta;
	cin.ignore ();
	cout << "Ingresa tu Nombre: ";
	cin.get (nuevo.nombre,30);
	cin.ignore ();

	for(int i = 0; i < carreras.size(); i++) {
		cout << i<<" Carreras Disponibles: " << carreras[i] << endl;
	}
	cout << "Ingrese Opcion: ";
	cin >> posicion;
	strcpy (nuevo.codigoPlan,carreras[posicion].c_str());
	nuevo.indiceAcademico = 0;
	nuevo.totClasesAprobadas = 0;
	archivoE.write (reinterpret_cast<const char *>(&nuevo),sizeof (EstudianteRegistro));
	archivoE.close ();
}
void Estudiante::ObtenerEstudiante () {
	ifstream archivoE ("Estudiante.dat",ios::binary);
	if(!archivoE) {
		cout << "Error al Leer el archivo";
		return;
	}
	archivoE.seekg (0,ios::beg);  //archivoE.seek(0,ios::end)
	EstudianteRegistro lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	cout << endl;
	while(!archivoE.eof ()) {
		cout << "Cuenta: " << lectura.numeroCuenta << endl;
		cout << "Nombre: " << lectura.nombre << endl;
		cout << "Codigo Plan: " << lectura.codigoPlan << endl;
		cout << "indiceAcademico: " << lectura.indiceAcademico << endl;
		cout << "totClasesAprobadas: " << clasesAprobadas() << endl;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	}
	archivoE.close ();
}

vector<string>Estudiante::ObtenerCarreras(){
	vector<string>carreras;
	Archivo a;
	MateriaFile clase;
	DIR *dir;
	dir = opendir ("C:\\Users\\Mauricio\\source\\repos\\Proyecto-II-SistemRegistro\\Proyecto-II-SistemRegistro\\PlanesEstudio");
	struct dirent *ent;
	if(dir == NULL) {
		cout << "error";
	}
	while((ent = readdir (dir)) != NULL) {
		if((strcmp (ent->d_name,".") != 0) && (strcmp (ent->d_name,"..") != 0)) {
			carreras.push_back (ent->d_name);
		}
	}
	return carreras;

}
int Estudiante::clasesAprobadas(){
	int clases = 0;
	ifstream archivoH ("HistorialAcademico.dat",ios::binary);
	if(!archivoH) {
		return false;
	}
	Matricula lectura;
	archivoH.seekg (0,ios::beg);
	archivoH.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	while(!archivoH.eof ()) {
		if(lectura.status) {
			clases++;
		}
		archivoH.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}
	archivoH.close ();
	return clases;
} 
/*
	int numeroCuenta;
	char nombre[45];
	char codigoPlan[7];
	float indiceAcademico;
	int totClasesAprobadas;
*/
