#pragma once
#ifndef PLAN_ESTUDIO_H
#define PLAN_ESTUDIO_H
#include <iostream>
#include <vector>
using namespace std;
struct MateriaFile {
	char codigo[7];
	char nombre[45];
	char nombreHijos[25]="";
	int uv;
	int cantHijos;
	MateriaFile (string _codigo,string _nombre,int uv,int cantHijos) {
		strcpy (codigo,_codigo.c_str ());
		strcpy (nombre,_nombre.c_str ());
		
		this->uv = uv;
		this->cantHijos = cantHijos;
	}
	MateriaFile () {}
};
struct materia {
	string codigo;
	string nombre;
	int uv;
	int cantHijos;
	string padre;
	vector<materia*>hijos;
	int posicion;
	materia (string _codigo,string _nombre,int _uv,string _padre) {
		this->codigo=_codigo.c_str();
		this->nombre=_nombre.c_str ();
		this->padre=_padre.c_str ();
		uv = _uv;
		cantHijos = 0;
		posicion = 0;
	}

};

class PlanEstudio {
private:
	materia **raiz;
	bool estaVacio ();
	void ImprimirRec (materia **raiz);
	materia **buscarRec (materia **,string);
	materia *buscarRec2 (materia *,string);
public:
	PlanEstudio ();
	void agregar (string codigo,string nombre,int uv,string CodigoPadre);
	materia **buscar (string);
	materia *buscar2 (string);
	vector<materia*>clases;
	void imprimir ();
	void ClasesDisponibles ();
	bool yaAprobo (string);
	void yaAproboSinReq (materia**);//caso para las clases sin req
	void yaAproboIdiomas (materia **,int);
	void yaAproboSubHijos (materia **);
	void padre (string);
	vector<materia*> padres (materia *,string);
	bool verificarAprobadas(int);
};
#endif // !PLAN_ESTUDIO_H
