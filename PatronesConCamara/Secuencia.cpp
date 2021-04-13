#include "Secuencia.h"

void Secuencia::ejecutarSecuencia(Pantalla* pantalla, Camaras* camaras, string path, string extension, bool enable_camera) {
	int cameraImage = 0;

	for (int i = 0; i < n; i++) {
		pantalla->borrarImagen();
		patrones[i]->cargarPatronBitmap(pantalla->getHwnd(), pantalla);
		Sleep(30);
		if (enable_camera) camaras->guardarImagenesEnDisco(path, path, extension, cameraImage++);
	}
}


int Secuencia::getIndexColor() {
	return indexColor;
}