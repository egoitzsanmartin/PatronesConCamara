#include <windows.h>
#include <iostream>
#include <string>
#include "Patron.h"
#include "PatronColor.h"
#include "PatronSinusoidal.h"
#include "Pantalla.h"
#include "InicializarPantalla.h"
#include "Camara.h"
#include "Camaras.h"
#include "Secuencia.h"
#include "SecuenciaSinusoidal.h"

static const string PATH = "C:/Users/Aita/Documents/aruco";
static const string EXTENSION = ".bmp";
static const bool ENABLE_CAMERA = false;
static const string CLASS_NAME = "myWindowClass";
static const int N = 100;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	registrarVentana(hInstance, CLASS_NAME);
	Pantalla* pantalla = new Pantalla(hInstance, CLASS_NAME);
	pantalla->crearVentana(CLASS_NAME);

	Camaras* camaras = NULL;
	Camara* camara = NULL;

	if (ENABLE_CAMERA) {
		camaras = new Camaras();
		camaras->inicializarCamara(0);
		camara = camaras->getCamara(0);
		camara->cambiarTiempoDeExposicion(30000);
	}

	SecuenciaSinusoidal* secuencia = new SecuenciaSinusoidal(VERTICAL, GREEN, 50, pantalla, N);
	secuencia->ejecutarSecuencia(pantalla, camara, PATH, EXTENSION, ENABLE_CAMERA);

	return 0;
}