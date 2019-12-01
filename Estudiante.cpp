#include "Estudiante.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void Estudiante::ingresarEstudiante () {
	ofstream archivoE ("Estudiante.dat",ios::out | ios::binary | ios::app);
	if(!archivoE) {
		cout << "Erro De Lectura en archivo";
		return;
	}
	int opcion = 0;
	EstudianteRegistro nuevo;
	cout << "Ingrese tu numero de cuenta:";
	cin >> nuevo.numeroCuenta;
	cin.ignore ();
	cout << "Ingresa tu Nombre: ";
	cin.get (nuevo.nombre,30);
	cin.ignore ();
	cout << "Escoge tu Plan: \n1.I-01-SISTEMAS COMPUTACIONALES";
	cin >> opcion;
	switch(opcion) {
	case 1:
		strcpy_s (nuevo.codigoPlan,7,"I-01");
		break;
	case 2:
		break;
	}

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
		cout << "totClasesAprobadas: " << lectura.totClasesAprobadas << endl;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	}
	archivoE.close ();
}
/*
	int numeroCuenta;
	char nombre[45];
	char codigoPlan[7];
	float indiceAcademico;
	int totClasesAprobadas;
*/