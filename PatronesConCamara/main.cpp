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
static const bool ENABLE_CAMERA = false;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	Pantalla* pantalla = new Pantalla(hInstance, CLASS_NAME);
	registrarVentana(hInstance, CLASS_NAME);
	pantalla->crearVentana(CLASS_NAME);

	Camaras* camaras;
	Camara* camara;

	if(ENABLE_CAMERA){

		camaras = new Camaras();
		camaras->inicializarCamara(0);
		camara = camaras->getCamara(0);
	}

	PatronSinusoidal* patronSinusoidalHorizontal = new PatronSinusoidal(VERTICAL, GREEN, 0, 50, pantalla->getHeight(), pantalla->getWidth());
	PatronSinusoidal* patronSinusoidalVertical = new PatronSinusoidal(HORIZONTAL, WHITE, 0, 50, pantalla->getHeight(), pantalla->getWidth());

	int cont = 0;
	while (true) {
	
		pantalla->borrarImagen();
		
		if (cont++ % 2 == 0) {
			patronSinusoidalHorizontal->cargarPatronBitmap(pantalla->getHwnd(), pantalla->getWidth(), pantalla->getHeight());
		}
		else {
			patronSinusoidalVertical->cargarPatronBitmap(pantalla->getHwnd(), pantalla->getWidth(), pantalla->getHeight());
		}

		waitKey(10);

		if (ENABLE_CAMERA) camara->guardarImagenEnDisco(PATH, EXTENSION, cameraImage++, camara->getImage(camaras->getManager()));
	}

	return 0;
}