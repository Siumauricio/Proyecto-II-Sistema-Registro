#include "Archivo.h"
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>
#include <regex>
#include "PlanEstudio.h"
#include <dirent.h>
#include "Estudiante.h"
#include <algorithm>
using namespace std;
Archivo::Archivo () {}
void Archivo::Menu () {
	bool cerrar = true;
	int opcion = 0;
	Estudiante e;
	Archivo a;
	a.cargarArbol ();
	do {
		cout << "1.Crear Plan Estudio" << endl;
		cout << "2.Crear Alumno" << endl;
		cout << "3.Planes De Estudio Disponibles" << endl;
		cout << "4. Iniciar / Cerrar Inscripcion de clases" << endl;
		cout << "5. Finalizar Periodo" << endl;
		cout << "6.Informacion Academica" << endl;
		cout << "7. Salir del Sistema" << endl;
		cout << "Ingrese Opcion: ";
		cin >> opcion;
		switch(opcion) {
		case 1:
			a.CrearPlanEstudio ();
			break;
		case 2:
			Estudiante e;
			remove ("HistorialAcademico.dat");
			e.ingresarEstudiante ();
			a.cargarArbol ();
			cout << "\n\n";
			break;
		case 3:
			cout << "\n-------PLANES DE ESTUDIO DISPONIBLES-------" << endl;
			a.LeerPlanesEstudio ();
			break;
		case 4:
			a.plan.ClasesDisponibles ();
			a.plan.MatricularClases ();
			cout << "\n\n";
			break;
		case 5:
			cout << "\n--------Finalizando Periodo Ingrese las Notas--------- " << endl;
			a.plan.subirNota ();
			cout << "\n\n";
			break;
		case 6:
			cout << "\n\n--------Historial Academico---------\n\n";
			e.ObtenerEstudiante ();
			cout << "\n\n";
			a.historialAcademico ();
			cout << "\n\n";
			break;
		case 7:
			cerrar = false;
			break;
		}
	} while(cerrar);

}

void Archivo::cargarArbol(){
	ifstream archivoE ("C:\\Users\\Mauricio\\source\\repos\\Proyecto-II-SistemRegistro\\Proyecto-II-SistemRegistro\\PlanesEstudio\\"+obtenerCarrera(),ios::binary);
	if(!archivoE) {
		//cout << "Error al Leer el archivo";
		return;
	}
	archivoE.seekg (0,ios::beg);
	MateriaFile lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (MateriaFile));
	while(!archivoE.eof ()) {
		plan.agregar (lectura.codigo,lectura.nombre,lectura.uv,lectura.padre);
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (MateriaFile));
	}
	cout << "\n";
	archivoE.close ();


}
void Archivo::LeerPlanesEstudio(){
	MateriaFile clase;
	DIR *dir;
	dir = opendir ("C:\\Users\\Mauricio\\source\\repos\\Proyecto-II-SistemRegistro\\Proyecto-II-SistemRegistro\\PlanesEstudio");
	struct dirent *ent;
	if(dir == NULL) {
		cout << "error";
	}
	while((ent = readdir (dir)) != NULL) {
		if((strcmp (ent->d_name,".") != 0) && (strcmp (ent->d_name,"..") != 0)) {
			MostrarPlanEstudio ((string)ent->d_name);
		}
	}


}
void Archivo::MostrarPlanEstudio (string nombre) {
	ifstream archivoE ("C:\\Users\\Mauricio\\source\\repos\\Proyecto-II-SistemRegistro\\Proyecto-II-SistemRegistro\\PlanesEstudio\\"+nombre,ios::binary);
	if(!archivoE) {
		cout << "Error al Leer el archivo";
		return;
	}
	archivoE.seekg (0,ios::beg);
	MateriaFile lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (MateriaFile));
	cout << "Plan " << nombre << endl;
	while(!archivoE.eof ()) {
		cout << "Codigo: " << lectura.codigo << " Nombre: " << lectura.nombre << " Padre: "<<lectura.padre<<" UV: " << lectura.uv <<  endl;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (MateriaFile));
	}
	cout << "\n";
	archivoE.close ();
}


void Archivo::CrearPlanEstudio () {
	string nombrePlan;
	cout << "\n";
	MateriaFile Escribir;
	int cantidad = 0;
	cout << "Ingrese el Nombre del Plan: ";
	cin >> nombrePlan;
	cin.ignore ();
	cout << "Ingrese Cantidad de clases: ";
	cin >> cantidad;
	cin.ignore ();
	fstream archivoE ("C:\\Users\\Mauricio\\source\\repos\\Proyecto-II-SistemRegistro\\Proyecto-II-SistemRegistro\\PlanesEstudio\\"+nombrePlan+".dat",ios::out | ios::binary | ios::app);
	for(int i = 0; i < cantidad; i++) {
	cout << "Ingrese el Codigo de la clase a guardar:";
	cin.getline (Escribir.codigo,7);
	cout << "Ingrese el Nombre de la clase a guardar:";
		cin.getline (Escribir.nombre,45);
		cout << "Ingrese Uv: ";
		cin >> Escribir.uv;
		cout << "Ingrese El Padre: ";
		cin.ignore ();
		cin.getline (Escribir.padre,7);
		archivoE.write (reinterpret_cast<const char *>(&Escribir),sizeof (MateriaFile));
		cout << "\n";
	}
	cout << "\n";
	archivoE.close ();
}

void Archivo::MatricularClases (string codigo,string nombre,int UV) {
	ofstream archivoE ("HistorialAcademico.dat",ios::out | ios::binary | ios::app);
	if(!archivoE) {
		cout << "Erro De Lectura en archivo";
		return;
	}
	Matricula nuevo;
	strcpy (nuevo.codigo,codigo.c_str ());
	strcpy (nuevo.nombre,nombre.c_str ());
	nuevo.uv = UV;
	nuevo.status = false;
	nuevo.nota = 0;
	archivoE.write (reinterpret_cast<const char *>(&nuevo),sizeof (Matricula));
	archivoE.close ();
}

string Archivo::obtenerCarrera () {
  	ifstream archivoE ("Estudiante.dat",ios::binary);
	if(!archivoE) {
		return "";
	}
	archivoE.seekg (0,ios::beg);  //archivoE.seek(0,ios::end)
	EstudianteRegistro lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	while(!archivoE.eof ()) {
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	}
	archivoE.close ();
	return lectura.codigoPlan;
}

void Archivo::modificarNota (string codigo,int nota) {
	fstream archivoE ("HistorialAcademico.dat",ios::in | ios::out | ios::binary);
	//fstream leer y ir modificando el valor
	if(!archivoE) {
		cout << "Error de lectura en el archivo";
	}
	archivoE.seekg (0,ios::beg);
	Matricula lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	int posicionregistro = 0;
	while(!archivoE.eof ()) {
		if(strcmp (lectura.codigo,codigo.c_str ()) == 0 && lectura.nota == 0) {
			if(nota >= 60) {
				lectura.nota = nota;
				lectura.status = true;
			} else {
				lectura.nota = nota;
				lectura.status = false;
			}
			archivoE.seekp (posicionregistro * sizeof (Matricula),ios::beg);
			archivoE.write (reinterpret_cast<const char *>(&lectura),sizeof (Matricula));
			archivoE.close ();
			return;
		}
		posicionregistro++;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}

	cout << "Registro No Encontrado";
	archivoE.close ();
}

void Archivo::historialAcademico () {
	ifstream archivoE ("HistorialAcademico.dat",ios::binary);
	if(!archivoE) {
		cout << "No Existe ningun registro Academico!";
		return;
	}
	int Uv = 0;
	float resultado = 0;
	archivoE.seekg (0,ios::beg);
	Matricula lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	while(!archivoE.eof ()) {
		Uv += lectura.uv;
		resultado += (lectura.nota) * lectura.uv;
		cout << "Codigo: " << lectura.codigo << " Nombre: " << lectura.nombre << " UV: " << lectura.uv << " Status: " << lectura.status << " Nota: " << lectura.nota << endl;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}
	resultado = (float)(resultado / Uv);
	cout << "\nPROMEDIO ACADEMICO: " << resultado;
	cout << "\n";
	archivoE.close ();
}

