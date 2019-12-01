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
	Materia Estructura[21];
	Archivo ();
	void ClasesDisponibles ();
	void MatricularClases (string,string,int);
	void modificarNota (string,int);
	string obtenerCarrera ();
	void historialAcademico ();
	int cantidadHijos (string);
	void LeerPlanEstudio ();
	void CrearPlanEstudio ();
	int codigoRepetido (string);
	bool yaAprobo (string,int);
	Matricula obtenerClase (string);
private:
	bool claseAprobada (string);
	void guardarInformacion ();

};
#endif // !ARCHIVO_H
