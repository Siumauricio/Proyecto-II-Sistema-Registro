#pragma once
#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <string>
#include "PlanEstudio.h"
#include <vector>
using namespace std;
struct Matricula {
	char codigo[7];
	char nombre[45];
	int nota;
	int uv;
	bool status = false;
};

class Archivo {
public:
	PlanEstudio plan;
	Archivo ();
	void MatricularClases (string,string,int);
	void modificarNota (string,int);
	string obtenerCarrera ();
	void historialAcademico ();
	void CrearPlanEstudio ();
	void LeerPlanesEstudio ();
	void Menu ();
	void MostrarPlanEstudio (string);
	void cargarArbol ();
private:
};
#endif // !ARCHIVO_H
