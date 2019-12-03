#include "PlanEstudio.h"
#include <queue>
#include<Windows.h>
PlanEstudio::PlanEstudio ():raiz (nullptr) {}

bool PlanEstudio::estaVacio () {
	return raiz == 0;
}
void PlanEstudio::agregar (string codigo,string nombre,int uv,string CodigoPadre) {
	materia *nueva = new materia (codigo,nombre,uv,CodigoPadre);
	if(estaVacio ()) {
		materia **tmpHijos = new materia * [1];
		tmpHijos[0] = nueva;
		raiz = tmpHijos;
		return;
	} else {
		if(CodigoPadre.empty ()) {
			(*raiz)->posicion += 1;
			materia **tmpHijos = new materia * [1];
			tmpHijos[0] = nueva;
			raiz[(*raiz)->posicion] = nueva;
			return;
		}
		if(buscar2 (codigo) == 0) {
			materia **tmpHijos = buscar (CodigoPadre);
			if(tmpHijos == nullptr) {
				return;
			}
			materia **tmpHijos2 = new materia * [1];
			tmpHijos2[0] = nueva;
			(*tmpHijos)->hijos.push_back (tmpHijos2[0]);
			tmpHijos[0]->cantHijos++;
		} else {
			materia **tmpHijos = buscar (CodigoPadre);
			if(tmpHijos == nullptr) {
				return;
			}
			materia **tmpHijos2 = new materia * [1];
			(*tmpHijos)->hijos.push_back ((*buscar (codigo)));
			tmpHijos[0]->cantHijos++;
		}
	}
}
materia *PlanEstudio::buscar2 (string codigoPadre) {
	if(raiz == 0) {
		return 0;
	} else {
		cout << endl;
		//cout << &*raiz << "  Codigo: " << (*raiz)->codigo << ",Nombre : " << (*raiz)->nombre << " Padre : " << (*raiz)->padre << " Memoria: " << endl;
		for(int i = 0; i <= (*raiz)->posicion; i++) {
			if(&raiz[i] != nullptr) {
				//cout << &*raiz << " " << raiz[i]->nombre << endl;
				if(buscarRec2 (&(*raiz[i]),codigoPadre) != nullptr) {
					return buscarRec2 (raiz[i],codigoPadre);
				}
			}
		}
	}
	return 0;
}

materia *PlanEstudio::buscarRec2 (materia *raiz,string codigoPadre) {
	int x = sizeof (raiz);
	if(raiz == 0) {
		return 0;
	}
	if(raiz->codigo == codigoPadre) {
		return raiz;
	}
	///cout << &*raiz << " " << (*raiz)->nombre << endl;
	for(int i = 0; i < raiz->cantHijos; i++) {
		materia *tmp = buscarRec2 (raiz->hijos[i],codigoPadre);
		if(tmp != 0) {
			return tmp;
		}
	}

	return 0;

}


materia **PlanEstudio::buscar (string codigoPadre) {
	if(raiz == 0) {
		return 0;
	} else {
		cout << endl;
		//cout << &*raiz << "  Codigo: " << (*raiz)->codigo << ",Nombre : " << (*raiz)->nombre << " Padre : " << (*raiz)->padre << " Memoria: " << endl;
		for(int i = 0; i <= (*raiz)->posicion; i++) {
			//cout << &*raiz << " " << raiz[i]->nombre << endl;
			if(buscarRec (&raiz[i],codigoPadre) != nullptr) {
				return buscarRec (&raiz[i],codigoPadre);
			}
		}
	}
	return 0;
}
materia **PlanEstudio::buscarRec (materia **raiz,string codigoPadre) {
	int x = sizeof (raiz);
	if(raiz == 0) {
		return 0;
	}
	if((*raiz)->codigo == codigoPadre) {
		return raiz;
	}
	///cout << &*raiz << " " << (*raiz)->nombre << endl;
	for(int i = 0; i < (*raiz)->cantHijos; i++) {
		materia **tmp = buscarRec (&(*raiz)->hijos[i],codigoPadre);
		if(tmp != 0) {
			return tmp;
		}
	}

	return 0;

}


void PlanEstudio::imprimir () {
	for(int i = 0; i <= (*raiz)->posicion; i++) {
		ImprimirRec (&raiz[i]);
	}
	// do stuff that may throw or fail
}

void PlanEstudio::ImprimirRec (materia **raiz) {
	if(raiz == 0) {
		return;
	}
	cout << *raiz << " Materia { codigo: " << (*raiz)->codigo << ", Nombre: " << (*raiz)->nombre << "}" << endl;
	for(int i = 0; i < (*raiz)->cantHijos; i++) {
		ImprimirRec (&(*raiz)->hijos[i]);
	}
}

