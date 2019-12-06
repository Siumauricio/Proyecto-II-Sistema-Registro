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
	MateriaFile Estructura[21];
	Archivo ();
	void ClasesDisponibles ();
	void MatricularClases (string,string,int);
	void modificarNota (string,int);
	string obtenerCarrera ();
	void historialAcademico ();
	int cantidadHijos (string);
	void LeerPlanEstudio (string,int);
	void CrearPlanEstudio ();
	int codigoRepetido (string);
	bool yaAproboHijos (string,int);
	Matricula obtenerClase (string);
	MateriaFile obtenerHijos (string);
	void LeerPlan2 (string ,int);
	void Menu ();
private:
	bool claseAprobada (string);
	void guardarInformacion ();
	void clasesR (string,int);
};
#endif // !ARCHIVO_H
