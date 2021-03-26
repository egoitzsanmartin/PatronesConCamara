#include "PatronSinusoidal.h"

PatronSinusoidal::PatronSinusoidal(int indexPatron, int indexColor, double phi0, double periodo, int rows, int cols) {
	PatronSinusoidal::phi0 = phi0;
	PatronSinusoidal::periodo = periodo;
	PatronSinusoidal::w = 2 * atan(1) * 4;

	switch (indexPatron) {
		case 0:
			generarPatronSinusoidalVertical(rows, cols, indexColor);
			break;
		case 1:
			generarPatronSinusoidalHorizontal(rows, cols, indexColor);
			break;
	}
	bitmap = matToBmp(*matriz);
	//bitmap = (HBITMAP)LoadImage(NULL, "C:/Users/Aita/Documents/aruco/img.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void PatronSinusoidal::generarPatronSinusoidalVertical(int rows, int cols, int indexColor) {
	Patron::matriz = new Mat(rows, cols, CV_8UC3);
	double value;

	for (double i = 0; i < cols; i++) {
		value = getCosValue(i);
		for (int j = 0; j < rows; j++) {
			matriz->row(j).col(i) = getColor(indexColor, value);
		}
	}
}

void PatronSinusoidal::generarPatronSinusoidalHorizontal(int rows, int cols, int indexColor) {
	Patron::matriz = new Mat(rows, cols, CV_8UC3);
	double value;

	for (double i = 0; i < rows; i++) {
		value = getCosValue(i);
		for (int j = 0; j < cols; j++) {
			matriz->row(i).col(j) = getColor(indexColor, value);
		}
	}
}

double PatronSinusoidal::getCosValue(double j) {
	return (1 + cos((w / periodo) * j + phi0))*255/2;
}


