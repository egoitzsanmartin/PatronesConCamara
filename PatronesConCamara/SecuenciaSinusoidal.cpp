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

void SecuenciaSinusoidal::ejecutarSecuencia(Pantalla* pantalla, Camara* camara, string path, string extension, bool enable_camera) {
	int cameraImage = 0;
	char buf[10];
	int periodoInt = periodo;
	sprintf_s(buf, 10, "%04d", periodoInt);

	string periodoString = buf;

	path = path + "/sinu/" + periodoString;

	if (indexPatron == VERTICAL) {
		path = path + "/V";
	}
	else if (indexPatron == HORIZONTAL){
		path = path + "/H";
	}

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

int SecuenciaSinusoidal::getIndexPatron() {
	return indexPatron;
}
