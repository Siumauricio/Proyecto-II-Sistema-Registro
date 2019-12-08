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
	do {
		Archivo a;
		a.CrearPlanEstudio ();
		cout << "1. Crear Plan de estudio " << endl;
		cout << "2. Iniciar / Cerrar Inscripcion de clases" << endl;
		cout << "3. Finalizar Periodo" << endl;
		cout << "4.Informacion Academica" << endl;
		cout << "5. Salir del Sistema" << endl;
		cout << "Ingrese Opcion: ";
		cin >> opcion;
		switch(opcion) {
		case 1:
			a.MostrarPlanEstudio ();
			break;
		case 2:
			a.plan.ClasesDisponibles ();
			a.plan.MatricularClases ();
			cout << "\n\n";
			break;
		case 3:
			cout << "\nFinalizando Periodo Ingrese las Notas: " << endl;
			a.plan.subirNota ();
			cout << "\n\n";
			break;
		case 4:
			cout << "\n\n--------HISTORIAL ACADEMICO---------\n\n";
			a.historialAcademico ();
			cout << "\n\n";
			break;
		case 5:
			cerrar = false;
			break;
		}
	} while(cerrar);

}
void Archivo::MostrarPlanEstudio () {
	//guardarInformacion ();
	for(int i = 0; i < size (Estructura); i++) {
		cout << " Codigo: " << Estructura[i].codigo << " Nombre: " << Estructura[i].nombre << endl;
	}
	cout << "\n";
}

int Archivo::cantidadHijos (string nombre) {
	int Hijos (0);
	stringstream ss (nombre);
	string word;
	while(ss >> word) ++Hijos;
	return Hijos;
}
void Archivo::CrearPlanEstudio () {
	guardarInformacion ();
	ofstream archivoE ("PlanDeEstudio.dat",ios::binary);
	if(!archivoE) {
		cout << "Erro De Lectura en archivo";
		return;
	}
	Matricula nuevo;
	for(int i = 0; i < size (Estructura); i++) {
		strcpy (nuevo.codigo,Estructura[i].codigo);
		strcpy (nuevo.nombre,Estructura[i].nombre);
		nuevo.uv = Estructura[i].uv;
		nuevo.nota = 0;
		nuevo.status = false;
		archivoE.write (reinterpret_cast<const char *>(&nuevo),sizeof (Matricula));
	}
	archivoE.close ();
	LeerPlanEstudio ("h",0);
}

void Archivo::LeerPlanEstudio (string codigo,int posicion) {
	Matricula lectura{0};
	for(int i = 0; i < size (Estructura); i++) {
		if(caso1) {
			stringstream ss (Estructura[i].nombreHijos);
			string word;
			plan.agregar (Estructura[i].codigo,Estructura[i].nombre,Estructura[i].uv,"");
			while(ss >> word) {
				arr.push_back (obtenerClase (word).codigo);
				plan.agregar (word.c_str (),obtenerClase (word).nombre,obtenerClase (word).uv,Estructura[i].codigo);
			}
			caso1 = false;
			caso2 = true;
		}if(caso2) {
			if(strcmp (Estructura[i].codigo,codigo.c_str ()) == 0) {
				stringstream ss (Estructura[i].nombreHijos);
				string word;
				if(Estructura[i].nombreHijos != "") {
					while(ss >> word) {
						if(obtenerClase (word).uv != 0) {
							arr.push_back (obtenerClase (word).codigo);
							plan.agregar (word.c_str (),obtenerClase (word).nombre,obtenerClase (word).uv,codigo.c_str ());
						}
					}
				}
			}
		}
	}
	if(posicion < arr.size ()) {
		auto end = arr.end ();
		for(auto it = arr.begin (); it != end; ++it) {
			end = std::remove (it + 1,end,*it);
		}
		arr.erase (end,arr.end ());
		LeerPlanEstudio (arr[posicion],posicion + 1);
	} else {
		LeerPlan2 ("",0,0);
		return;
	}
}

void Archivo::LeerPlan2 (string codigo,int posicion,int posi) {
	//clases sin requisito
	if(case3) {
		bool primero = true;
		for(int i = 0; i < size (Estructura); i++) {
			if(codigoRepetido (Estructura[i].codigo) == 1 && cantidadHijos (Estructura[i].nombreHijos) == 0) {
				if(primero) {
					plan.agregar (Estructura[i].codigo,Estructura[i].nombre,Estructura[i].uv,"");
					primero = false;
				}
				SinRequisitos.push_back (Estructura[i]);
			}
		}
		int pos = 0;
		for(int i = 1; i < SinRequisitos.size (); i++) {
			plan.agregar (SinRequisitos[i].codigo,SinRequisitos[i].nombre,SinRequisitos[i].uv,SinRequisitos[pos].codigo);
			pos++;
		}
		case3 = false;
		case4 = true;
	}
	//clases de idioma
	for(int i = 0; i < size (Estructura); i++) {
		if(case4) {
			if(codigoRepetido (Estructura[i].codigo) == 1 && cantidadHijos (Estructura[i].nombreHijos) == 1) {
				if(hola) {
					plan.agregar (Estructura[i].codigo,Estructura[i].nombre,Estructura[i].uv,"");
					ofi.push_back (Estructura[i].codigo);
					case4 = false;
					case5 = true;
				}
				if(arreglar) {
					plan.agregar (Estructura[i].codigo,Estructura[i].nombre,Estructura[i].uv,"");
					Idiomas.push_back (Estructura[i].codigo);
					arreglar = false;
					hola = true;
				}
			}
		}
		if(caso6) {
			if(strcmp (Estructura[i].codigo,codigo.c_str ()) == 0) {
				stringstream ss (Estructura[i].nombreHijos);
				string word;
				if(Estructura[i].nombreHijos != "") {
					while(ss >> word) {
						if(obtenerClase (word).uv != 0) {
							ofi.push_back (word);
							plan.agregar (word.c_str (),obtenerClase (word).nombre,obtenerClase (word).uv,codigo.c_str ());
						}
					}
				}
			}
		}
		if(case5) {
			if(strcmp (Estructura[i].codigo,codigo.c_str ()) == 0) {
				stringstream ss (Estructura[i].nombreHijos);
				string word;
				if(Estructura[i].nombreHijos != "") {
					while(ss >> word) {
						if(obtenerClase (word).uv != 0) {
							Idiomas.push_back (word);
							plan.agregar (word.c_str (),obtenerClase (word).nombre,obtenerClase (word).uv,codigo.c_str ());
						}
					}
				}
			}
		}
	}
	if(posicion < Idiomas.size ()) {
		LeerPlan2 (Idiomas[posicion],posicion + 1,posi);
	} else {
		case5 = false;
		caso6 = true;
		if(posi < ofi.size ()) {
			LeerPlan2 (ofi[posi],posicion,posi + 1);
		} else {
			plan.imprimir ();
			return;

		}
	}
}

int Archivo::codigoRepetido (string codigo) {
	guardarInformacion ();
	int contador = 0;
	for(int j = 0; j < size (Estructura); j++) {
		if(codigo == Estructura[j].codigo) {
			contador++;
		}
		stringstream ss (Estructura[j].nombreHijos);
		string word;
		while(ss >> word) {

			if(codigo == word) {
				contador++;
			}
		}
	}
	return contador;
}

Matricula Archivo::obtenerClase (string codigo) {
	ifstream archivoE ("PlanDeEstudio.dat",ios::binary);
	archivoE.seekg (0,ios::beg);
	Matricula lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	while(!archivoE.eof ()) {
		if(strcmp (codigo.c_str (),lectura.codigo) == 0) {
			return lectura;
		}
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}
	archivoE.close ();
	lectura = {0};
	return lectura;
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
	archivoE.seekg (0,ios::beg);  //archivoE.seek(0,ios::end)
	EstudianteRegistro lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	while(!archivoE.eof ()) {
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (EstudianteRegistro));
	}
	archivoE.close ();
	return  lectura.codigoPlan;
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
		cout << "Error al Leer el archivo";
		return;
	}
	archivoE.seekg (0,ios::beg);
	Matricula lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	while(!archivoE.eof ()) {
		cout << "Codigo: " << lectura.codigo << " Nombre: " << lectura.nombre << " UV: " << lectura.uv << " Status: " << lectura.status << " Nota: " << lectura.nota << endl;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}
	cout << "\n";
	archivoE.close ();
}


void Archivo::guardarInformacion () {
	int i = 0;
	ifstream in (obtenerCarrera () + ".txt");
	Archivo a;
	string cadena;
	smatch match;
	smatch match2;
	smatch match3;
	smatch match4;
	while(!in.eof ()) {
		if(!in.is_open ()) {
			cerr << "File can't be opened! " << endl;
			return;
		}
		getline (in,cadena);
		istringstream entrada (cadena);
		if(cadena.find ("Nombre") != std::string::npos) {
			string line (cadena);
			regex re ("Nombre=(.*)-");
			if(regex_search (line,match,re)) {
				string nombre = match[1];
				strcpy (Estructura[i].nombre,nombre.c_str ());
			}
		}
		istringstream entrada2 (cadena);
		if(cadena.find ("Codigo") != std::string::npos) {
			string line (cadena);
			regex re ("Codigo=(.*)'");
			if(regex_search (line,match2,re)) {
				string codigo = match2[1];
				strcpy (Estructura[i].codigo,codigo.c_str ());
			}
		}
		istringstream entrada3 (cadena);
		if(cadena.find ("UV") != std::string::npos) {
			string line (cadena);
			regex re ("UV=(.*),");
			if(regex_search (line,match3,re)) {
				string UV = match3[1];
				Estructura[i].uv = atoi (UV.c_str ());
			}
		}
		istringstream entrada4 (cadena);
		if(cadena.find ("Clases") != std::string::npos) {
			string line (cadena);
			regex re ("Clases=(.*)");
			if(regex_search (line,match4,re)) {
				string hijos = match4[1];
				strcpy (Estructura[i].nombreHijos,hijos.c_str ());
				Estructura[i].cantHijos = a.cantidadHijos (hijos);
			}
		}
		i++;
	}

}
