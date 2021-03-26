#include <iostream>
#include <windows.h>
#include "Patron.h"
#include "Pantalla.h"
#include "Camara.h"
#include "Camaras.h"

#ifndef SECUENCIA_H
#define SECUENCIA_H

using namespace std;
using namespace cv;

class Secuencia
{

public:
	Patron** patrones;
	int n;
	int indexColor;
	virtual void ejecutarSecuencia(Pantalla* pantalla, Camara* camara, string path, string extension, bool enable_camera);
	int getIndexColor();
};

#endif
