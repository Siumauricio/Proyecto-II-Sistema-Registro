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
	bool caso1 = true;//Extrae El Padre y lo agrega al arbol
	bool caso2 = false;//agrega sus hijos a un vector y dicho vector se recorre recursivamente
	bool case3 = true;//Caso para las clases sin requisito
	bool case4 = false;//Caso para los idiomas
	bool case5 = false;
	vector<MateriaFile>SinRequisitos;
	vector<string>Idiomas;
	vector<string>Hijos;
	vector<string>arr;
	PlanEstudio plan;
	MateriaFile Estructura[21];
	Archivo ();
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
