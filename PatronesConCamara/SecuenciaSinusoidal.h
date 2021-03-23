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
	SecuenciaSinusoidal(int indexPatron, int indexColor, double periodo, Pantalla* pantalla, int n);
};

#endif