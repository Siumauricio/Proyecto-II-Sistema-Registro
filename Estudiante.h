#pragma once
#ifndef EMPLEADO_H
#define EMPLEADO_H
#include <string>
using namespace std;
struct EstudianteRegistro {
	int numeroCuenta;
	char nombre[30];
	char codigoPlan[7];
	float indiceAcademico;
	int totClasesAprobadas;
};
class Estudiante {
public:
	 void ingresarEstudiante ();
	 void ObtenerEstudiante ();

};
#endif // !EMPLEADO_H
