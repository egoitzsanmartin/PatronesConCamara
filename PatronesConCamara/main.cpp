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

int cameraImage = 0;
static const string PATH = "C:/Users/Aita/Documents/aruco";
static const string EXTENSION = ".bmp";
static const string CLASS_NAME = "myWindowClass";
static const bool ENABLE_CAMERA = true;
static const int N = 100;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	Pantalla* pantalla = new Pantalla(hInstance, CLASS_NAME);
	registrarVentana(hInstance, CLASS_NAME);
	pantalla->crearVentana(CLASS_NAME);

	Camaras* camaras;
	Camara* camara;

	if (ENABLE_CAMERA) {

		camaras = new Camaras();
		camaras->inicializarCamara(0);
		camara = camaras->getCamara(0);
		camara->cambiarTiempoDeExposicion(30000, camaras->getManager());
	}

	Patron* patrones[N];

	double phi0 = (2 * (atan(1) * 4) / N) * 0;

	for (int i = 0; i < N; i++) {
		patrones[i] = new PatronSinusoidal(VERTICAL, GREEN, phi0, 50, pantalla->getHeight(), pantalla->getWidth());
		phi0 = (2 * (atan(1) * 4) / N) * i;
	}

	for(int i = 0; i < N; i++) {
	
		pantalla->borrarImagen();
		
		patrones[i]->cargarPatronBitmap(pantalla->getHwnd(), pantalla->getWidth(), pantalla->getHeight());

		Sleep(30);

		if (ENABLE_CAMERA) camara->guardarImagenEnDisco(PATH, EXTENSION, cameraImage++, camara->getImage(camaras->getManager()));
	}

	getchar();

	return 0;
}