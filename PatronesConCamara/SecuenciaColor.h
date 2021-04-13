#include <iostream>
#include <windows.h>
#include "Secuencia.h"
#include "PatronColor.h"

#ifndef SECUENCIA_COLOR_H
#define SECUENCIA_COLOR_H

using namespace std;
using namespace cv;

class SecuenciaColor : public Secuencia
{

public:
	SecuenciaColor(int indexColor, int inicio, int fin, int salto, Pantalla* pantalla);
	void ejecutarSecuencia(Pantalla* pantalla, Camaras* camaras, string path, string extension, bool enable_camera) override;
};

#endif