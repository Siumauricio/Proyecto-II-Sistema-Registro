#include "PlanEstudio.h"
PlanEstudio::PlanEstudio():raiz(0){}

bool PlanEstudio::estaVacio(){
	return raiz == 0;
}

void PlanEstudio::agregarMateria (string codigo,string nombre,int uv,string CodigoPadre) {
	Materia *nueva = new Materia (codigo,nombre,uv);
	if(estaVacio ()) {
		raiz = nueva;
		return;
	}
	Materia *padre = buscar (CodigoPadre);
	if(padre == 0) {
		cout << "Codigo de clase requisisto incorrecto!";
		delete nueva;
		return;
	}
	//crear copia de hijos
	Materia **tmpHijos = new Materia * [padre->cantHijos + 1]; //declarando un arreglo de apuntadores
	for(int i = 0; i < padre->cantHijos; i++) {
		tmpHijos[i] = padre->hijos[i];
	}
	tmpHijos[padre->cantHijos] = nueva;

	if(padre->cantHijos != 0) {
		delete padre->hijos;
	}
	padre->cantHijos++;
	padre->hijos = tmpHijos;
	cout << "Materia Ingresada!" << endl;
}
Materia* PlanEstudio::buscar(string codigoPadre){
	return buscarRec(raiz,codigoPadre);
	
}
Materia *PlanEstudio::buscarRec (Materia *raiz,string codigoPadre){
	if(raiz==0) {
		return 0;
	}
	if(raiz->codigo==codigoPadre) {
		return raiz;
	}
	for(int i = 0; i < raiz->cantHijos; i++) {
		Materia *tmp = buscarRec (raiz->hijos[i],codigoPadre);
		if(tmp!=0) {
			return tmp;
		}
	}
	return 0;

}
void PlanEstudio::imprimir(){
	ImprimirRec (raiz);
}
void PlanEstudio::ImprimirRec(Materia*raiz){
	if(raiz==0) {
		return;
	}else{
		cout << "Materia {Codigo: " << raiz->codigo << ", Nombre: " << raiz->nombre << " }\n";
		for(int i = 0; i < raiz->cantHijos; i++) {
			ImprimirRec (raiz->hijos[i]);
		}
	}
}