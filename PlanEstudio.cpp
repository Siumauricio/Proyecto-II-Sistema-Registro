#include "PlanEstudio.h"
#include <queue>
#include<Windows.h>
#include <set>
#include "Archivo.h"
#include <fstream>
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
		if(CodigoPadre.empty ()) {//Cuando un Padre viene con codigo padre vacio
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
		for(int i = 0; i <= (*raiz)->posicion; i++) {
			if(&raiz[i] != nullptr) {
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
		for(int i = 0; i <= (*raiz)->posicion; i++) {
			if(buscarRec (&raiz[i],codigoPadre) != nullptr) {
				return buscarRec (&raiz[i],codigoPadre);
			}
		}
	}
	return 0;
}
materia **PlanEstudio::buscarRec (materia **raiz,string codigoPadre) {
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
	if((*raiz)->posicion == 0) {
		ImprimirRec (&raiz[0]);
	} else {
		for(int i = 0; i <= (*raiz)->posicion; i++) {
			cout << endl;
			clases.push_back (raiz[i]);
			ImprimirRec (&raiz[i]);
		}
	}
}

void PlanEstudio::ImprimirRec (materia **raiz) {
	if(raiz == 0) {
		return;
	}
	//cout << " Materia { codigo: " << (*raiz)->codigo << ", Nombre: " << (*raiz)->nombre << "}" << endl;
	for(int i = 0; i < (*raiz)->cantHijos; i++) {
		ImprimirRec (&(*raiz)->hijos[i]);
	}
}

void PlanEstudio::ClasesDisponibles () {
	Archivo a;
	cout << "\n\nClases Disponibles: " << endl;
	for(int i = 0; i < clases.size (); i++) {
		if(i == 1) {//Caso para las clases sin requisitos
			yaAproboSinReq (&clases[i]);
		} else {
			if(!yaAprobo (clases[i]->codigo)) {
				cout << " Materia { codigo: " << clases[i]->codigo << ", Nombre: " << clases[i]->nombre << "}" << endl;
			} else {
				if(raiz[i]->cantHijos == 1) {//Caso para Idiomas
					yaAproboIdiomas (&raiz[i],raiz[i]->cantHijos);
				} else {
					yaAproboSubHijos (&raiz[i]);

				}
			}
		}
	}
	//a.MatricularClases (clases[0]->codigo,clases[0]->nombre,clases[0]->uv);
}
vector<materia *>padress;
vector<materia *>apro;
vector<string>verificadas;
bool vez1 = true;

bool PlanEstudio::verificarAprobadas (int contador) {
	for(int i = 0; i < padress.size (); i++) {
		if(yaAprobo (padress[i]->codigo)) {
			contador++;
		}
	}
	return contador = (contador == padress.size () && padress.size () != 0) ? true : false;
}
void PlanEstudio::yaAproboSubHijos (materia **raiz) {
	if(raiz == 0) {
		return;
	}
	padre ((*raiz)->codigo);
	if(verificarAprobadas (0)) {
		if(!yaAprobo(apro[0]->codigo)) {
			bool temporal = true;
			for(int i = 0; i < verificadas.size(); i++) {
				if(verificadas[i]==apro[0]->codigo){
					temporal = false;
					break;
				}
			}
			if(temporal) {
				verificadas.push_back (apro[0]->codigo);
				cout << " Materia { codigo: " << apro[0]->codigo << ", Nombre: " << apro[0]->nombre << "}" << endl;
			}
			//cout << " Materia { codigo: " << apro[0]->codigo << ", Nombre: " << apro[0]->nombre << "}" << endl;
			padress.clear ();
			apro.clear ();
		}
		padress.clear ();
		apro.clear ();
	} else {
		padress.clear ();
		apro.clear ();
	}

	for(int i = 0; i < (*raiz)->cantHijos; i++) {
		//if(!yaAprobo ((*raiz)->hijos[i]->codigo) && yaAprobo ((*raiz)->codigo)) {
		//	cout << " Materia { codigo: " << (*raiz)->hijos[i]->codigo << ", Nombre: " << (*raiz)->hijos[i]->nombre << "}" << endl;
		//}
		yaAproboSubHijos (&(*raiz)->hijos[i]);
	}
}
void PlanEstudio::padre (string codigo) {
	padres ((*raiz),codigo);
}

int posicion = 0;
vector<materia *> PlanEstudio::padres (materia *raiz,string codigo) {
	int x = sizeof (raiz);
	if(raiz == 0) {
		return padress;
	}
	for(int i = 0; i < raiz[0].hijos.size (); i++) {
		if(raiz[0].hijos[i]->codigo == codigo) {
			apro.push_back (raiz[0].hijos[i]);
			padress.push_back (raiz);
		}
	}
	///cout << &*raiz << " " << (*raiz)->nombre << endl;
	for(int i = 0; i < raiz->cantHijos; i++) {
		posicion = i;
		padres (raiz->hijos[i],codigo);
	}
	return padress;
}


void PlanEstudio::yaAproboIdiomas (materia **raiz,int contador) {
	if(raiz == 0) {
		return;
	}
	if(!yaAprobo ((*raiz)->codigo) && yaAprobo ((*raiz)->padre)) {
		cout << " Materia { codigo: " << (*raiz)->codigo << ", Nombre: " << (*raiz)->nombre << "}" << endl;
	}
	for(int i = 0; i < (*raiz)->cantHijos; i++) {
		yaAproboIdiomas (&(*raiz)->hijos[i],contador);
	}
}
void PlanEstudio::yaAproboSinReq (materia **raiz) {
	if(raiz == 0) {
		return;
	}
	if(!yaAprobo ((*raiz)->codigo)) {
		cout << " Materia { codigo: " << (*raiz)->codigo << ", Nombre: " << (*raiz)->nombre << "}" << endl;
	}

	for(int i = 0; i < (*raiz)->cantHijos; i++) {
		yaAproboSinReq (&(*raiz)->hijos[i]);
	}
}

bool PlanEstudio::yaAprobo (string codigo) {

	ifstream archivoH ("HistorialAcademico.dat",ios::binary);
	if(!archivoH) {
		return false;
	}
	Matricula lectura;
	archivoH.seekg (0,ios::beg);
	archivoH.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	while(!archivoH.eof ()) {
		if(strcmp (codigo.c_str (),lectura.codigo) == 0 && lectura.status == true) {
			return true;
		}
		archivoH.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}
	archivoH.close ();
	return false;

}
