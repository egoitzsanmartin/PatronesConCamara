#include "SecuenciaColor.h"

SecuenciaColor::SecuenciaColor(int indexColor, int inicio, int fin, int salto, Pantalla* pantalla) {
	int cantidad = (fin - inicio) / salto;
	Secuencia::n = cantidad + 1;
	Secuencia::patrones = new Patron*[n];
	Secuencia::indexColor = indexColor;
	double intensidad;
	int count = 0;

	for (int i = inicio; i < fin + 1; i=i+salto) {
		intensidad = i;
		patrones[count++] = new PatronColor(indexColor, intensidad, pantalla->getHeight(), pantalla->getWidth());
	}
}

void SecuenciaColor::ejecutarSecuencia(Pantalla* pantalla, Camaras* camaras, string path, string extension, bool enable_camera) {
	int cameraImage = 0;
	string relativePath;

	relativePath = "/color";

	if (indexColor == RED) {
		relativePath = relativePath + "/R/";
	}
	else if (indexColor == GREEN) {
		relativePath = relativePath + "/G/";
	}
	else if (indexColor == BLUE) {
		relativePath = relativePath + "/B/";
	}
	else if (indexColor == WHITE) {
		relativePath = relativePath + "/W/";
	}
	pantalla->borrarImagen();
	patrones[0]->cargarPatronBitmap(pantalla->getHwnd(), pantalla);
	for (int i = 0; i < n; i++) {
		
		Sleep(30);
		if (enable_camera) {
			camaras->getImages(n);
			if (i + 1 < n) {
				pantalla->borrarImagen();
				patrones[i + 1]->cargarPatronBitmap(pantalla->getHwnd(), pantalla);
			}
			camaras->guardarImagenesEnDisco(path, relativePath, extension, n);
		}
	}
}

