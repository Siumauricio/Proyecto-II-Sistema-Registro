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
}
void Archivo::LeerPlanEstudio () {
	ifstream archivoE ("PlanDeEstudio.dat",ios::binary);
	if(!archivoE) {
		cout << "Error al Leer el archivo";
		return;
	}
	archivoE.seekg (0,ios::beg);
	Matricula lectura;
	archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	while(!archivoE.eof ()) {
		cout << "Codigo: " << lectura.codigo << endl;
		cout << "Nombre: " << lectura.nombre << endl;
		cout << "UV: " << lectura.uv << endl;
		cout << "Status: " << lectura.status << endl;
		cout << "Nota: " << lectura.nota << endl;
		cout << "-------------------" << endl;
		archivoE.read (reinterpret_cast<char *>(&lectura),sizeof (Matricula));
	}
	archivoE.close ();
}
bool caso1 = true;

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

bool Archivo::yaAprobo (string codigo,int cantidad) {
	int contador = 0;
	for(int i = 0; i < size (Estructura); i++) {
		stringstream ss (Estructura[i].nombreHijos);
		string word;
		while(ss >> word) {
			if(codigo == word && claseAprobada (Estructura[i].codigo)) {
				contador++;
			}
		}

	}
	if(cantidad - 1 == contador) {
		return true;
	}
	return false;
}

void Archivo::ClasesDisponibles () {
	if(caso1) {

		guardarInformacion ();
		vector<Matricula>aprobadas;
		for(int i = 0; i < size (Estructura); i++) {
			if(codigoRepetido (Estructura[i].codigo) == 1 && !claseAprobada (Estructura[i].codigo)) {
				aprobadas.push_back (obtenerClase (Estructura[i].codigo));
			} else if(codigoRepetido (Estructura[i].codigo) > 2) {
				if(yaAprobo (Estructura[i].codigo,codigoRepetido (Estructura[i].codigo))&&!claseAprobada(Estructura[i].codigo)) {
						aprobadas.push_back (obtenerClase (Estructura[i].codigo));
				}
			} 
		}
		for(int i = 0; i < size (Estructura); i++) {
				if(claseAprobada (Estructura[i].codigo)) {
					stringstream ss (Estructura[i].nombreHijos);
					string word;
					while(ss >> word) {
						if(word.empty ()) {
							break;
						} else {
							if(!claseAprobada (word)&& codigoRepetido (word) ==2) {
								bool existe = true;
								for(int i = 0; i < aprobadas.size (); i++) {
									if(strcmp (aprobadas[i].codigo,word.c_str ()) == 0) {
										existe = false;
									}
								}
								if(existe) {
									aprobadas.push_back (obtenerClase (word));
								}
							}
						}
				}
			}
		}
		cout << endl;
		for(int i = 0; i < aprobadas.size (); i++) {
			if(strcmp (aprobadas[i].codigo,"") != 0) {
				cout << i << ". " << aprobadas[i].codigo << " | ";
				cout << " " << aprobadas[i].nombre << " | ";
				cout << " " << aprobadas[i].uv << " | ";
				cout << endl;
			}
		}
		int posicion = 0;
		cout << "Escriba la Clase a Matricular: ";
		cin >> posicion;
		MatricularClases (aprobadas[posicion].codigo,aprobadas[posicion].nombre,aprobadas[posicion].uv);
	}
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


bool Archivo::claseAprobada (string codigo) {
	ifstream archivoH ("HistorialAcademico.dat",ios::binary);
	if(!archivoH) {
		//cout << "Error al Leer el archivo";
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
	return false;
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