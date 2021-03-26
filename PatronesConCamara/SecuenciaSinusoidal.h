#include <iostream>
#include <windows.h>
#include "Secuencia.h"
#include "PatronSinusoidal.h"


#ifndef SECUENCIA_SINUSOIDAL_H
#define SECUENCIA_SINUSOIDAL_H

using namespace std;
using namespace cv;

class SecuenciaSinusoidal : public Secuencia
{

public:
	int indexPatron;
	double periodo;
	SecuenciaSinusoidal(int indexPatron, int indexColor, double periodo, int n, Pantalla* pantalla);
	void ejecutarSecuencia(Pantalla* pantalla, Camara* camara, string path, string extension, bool enable_camera) override;
	int getIndexPatron();
};

#endif