#pragma once
#ifndef PLAN_ESTUDIO_H
#define PLAN_ESTUDIO_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
using namespace std;
struct MateriaFile {
	char codigo[7];
	char nombre[45];
	//char nombreHijos[30];
	int uv;
	int cantHijos;
	char padre[7];
	
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
	vector<materia *>hijos;
	int posicion;
	materia (string _codigo,string _nombre,int _uv,string _padre) {
		this->codigo = _codigo.c_str ();
		this->nombre = _nombre.c_str ();
		this->padre = _padre.c_str ();
		uv = _uv;
		cantHijos = 0;
		posicion = 0;
	}
	materia(){}
	
};

class PlanEstudio {
private:
	materia **raiz;
	bool estaVacio ();
	void ImprimirRec (materia **raiz);
	materia **buscarRec (materia **,string);
	materia *buscarRec2 (materia *,string);
public:
	vector<materia *>padres;
	vector<materia *>aprobadas;
	vector<materia >clasesDisponibles;
	vector<materia >aplicarNota;
	int posicion = 0;
	PlanEstudio ();
	void agregar (string codigo,string nombre,int uv,string CodigoPadre);
	materia **buscar (string);
	materia *BuscarPadres (string);
	void imprimir ();
	void ClasesDisponibles ();
	bool yaAprobo (string);
	void yaAproboSubHijos (materia **);
	void Padres (string);
	void extraerPadres (materia *,string);
	bool verificarAprobadas (int);
	void MatricularClases ();
	void subirNota ();
};
#endif // !PLAN_ESTUDIO_H
