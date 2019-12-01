#pragma once
#ifndef PLAN_ESTUDIO_H
#define PLAN_ESTUDIO_H
#include <iostream>
using namespace std;
struct Materia {
	char codigo[7];
	char nombre[45];
	char nombreHijos[25];
	int uv;
	int cantHijos;
	Materia **hijos;
	Materia (string _codigo,string _nombre,int uv) {
		this->codigo[_codigo.size () + 1];
		_codigo.copy (this->codigo,_codigo.size () + 1);
		this->codigo[_codigo.size ()] = '\0';

		this->nombre[_nombre.size () + 1];
		_nombre.copy (this->nombre,_nombre.size () + 1);
		this->nombre[_nombre.size ()] = '\0';

		this->uv = uv;
		this->cantHijos = 0;
		hijos = 0;
	}
	bool operator==(const Materia &rhs) const {
		if(codigo != rhs.codigo)
			return true;
		return false;
	}
	Materia () {}
};


class PlanEstudio {
private:
	Materia *raiz;
	bool estaVacio ();
	void ImprimirRec (Materia*raiz);
	Materia *buscarRec (Materia *,string);
public:

	PlanEstudio ();
	void agregarMateria (string,string,int,string);
	Materia *buscar (string);
	void imprimir ();

};
#endif // !PLAN_ESTUDIO_H
