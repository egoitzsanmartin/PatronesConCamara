#include "SecuenciaSinusoidal.h"

SecuenciaSinusoidal::SecuenciaSinusoidal(int indexPatron, int indexColor, double periodo, int n, Pantalla* pantalla) {
	Secuencia::n = n;
	double phi0;
	Secuencia::patrones = new Patron*[n];
	Secuencia::indexColor = indexColor;
	SecuenciaSinusoidal::indexPatron = indexPatron;
	SecuenciaSinusoidal::periodo = periodo;

	for (int i = 0; i < n; i++) {
		phi0 = (2 * (atan(1) * 4) / n) * i;
		patrones[i] = new PatronSinusoidal(indexPatron, indexColor, phi0, periodo, pantalla->getHeight(), pantalla->getWidth());
	}
}

void SecuenciaSinusoidal::ejecutarSecuencia(Pantalla* pantalla, Camaras* camaras, string path, string extension, bool enable_camera) {
	int cameraImage = 0;
	char buf[10];
	int periodoInt = periodo;
	string relativePath;
	sprintf_s(buf, 10, "%04d", periodoInt);

	string periodoString = buf;

	relativePath = "/sinu/" + periodoString;

	if (indexPatron == VERTICAL) {
		relativePath = relativePath + "/V";
	}
	else if (indexPatron == HORIZONTAL){
		relativePath = relativePath + "/H";
	}

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

	for (int i = 0; i < n; i++) {
		pantalla->borrarImagen();
		patrones[i]->cargarPatronBitmap(pantalla->getHwnd(), pantalla);
		Sleep(30);
		if (enable_camera) camaras->guardarImagenesEnDisco(path, relativePath, extension, cameraImage++);
	}
}

int SecuenciaSinusoidal::getIndexPatron() {
	return indexPatron;
}
