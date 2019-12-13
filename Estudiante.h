#pragma once
#ifndef EMPLEADO_H
#define EMPLEADO_H
#include <string>
#include <vector>
using namespace std;
struct EstudianteRegistro {
	int numeroCuenta;
	char nombre[30];
	char codigoPlan[25];
	float indiceAcademico;
	int totClasesAprobadas;
};
class Estudiante {
public:
	void ingresarEstudiante ();
	void ObtenerEstudiante ();
	vector<string> ObtenerCarreras ();
	int clasesAprobadas ();
};
#endif // !EMPLEADO_H
