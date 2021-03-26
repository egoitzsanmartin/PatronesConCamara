#include "Secuencia.h"

void Secuencia::ejecutarSecuencia(Pantalla* pantalla, Camara* camara, string path, string extension, bool enable_camera) {
	int cameraImage = 0;

	for (int i = 0; i < n; i++) {
		pantalla->borrarImagen();
		patrones[i]->cargarPatronBitmap(pantalla->getHwnd(), pantalla);
		Sleep(30);
		if (enable_camera) camara->guardarImagenEnDisco(path, extension, cameraImage++, camara->getImage());
	}
}


int Secuencia::getIndexColor() {
	return indexColor;
}