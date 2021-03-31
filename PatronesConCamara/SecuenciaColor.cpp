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

void SecuenciaColor::ejecutarSecuencia(Pantalla* pantalla, Camara* camara, string path, string extension, bool enable_camera) {
	int cameraImage = 0;
	path = path + "/color";

	if (indexColor == RED) {
		path = path + "/R/";
	}
	else if (indexColor == GREEN) {
		path = path + "/G/";
	}
	else if (indexColor == BLUE) {
		path = path + "/B/";
	}
	else if (indexColor == WHITE) {
		path = path + "/W/";
	}

	for (int i = 0; i < n; i++) {
		pantalla->borrarImagen();
		patrones[i]->cargarPatronBitmap(pantalla->getHwnd(), pantalla);
		Sleep(30);
		if (enable_camera) camara->guardarImagenEnDisco(path, extension, cameraImage++, camara->getImage());
	}
}

