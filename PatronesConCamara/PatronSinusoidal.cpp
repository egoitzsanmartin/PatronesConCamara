#include "PatronSinusoidal.h"

PatronSinusoidal::PatronSinusoidal(int indexPatron, int indexColor, int phi0, int periodo, int rows, int cols) {
	PatronSinusoidal::phi0 = phi0;
	PatronSinusoidal::periodo = periodo;
	PatronSinusoidal::w = 2 * atan(1) * 4;

	switch (indexPatron) {
		case 0:
			generarPatronSinusoidalVertical(rows, cols);
			break;
		case 1:
			generarPatronSinusoidalHorizontal(rows, cols);
			break;
	}
	bitmap = Patron::matToBmp(*matriz);
	//bitmap = (HBITMAP)LoadImage(NULL, "C:/Users/Aita/Documents/aruco/img.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void PatronSinusoidal::generarPatronSinusoidalVertical(int rows, int cols) {
	Patron::matriz = new Mat(rows, cols, CV_8UC3);
	double value;

	for (int i = 0; i < rows; i++) {
		for (double j = 0; j < cols; j++) {
			value = getCosValue(j);
			matriz->row(i).col(j) = Scalar(value, value, value);
		}
	}
}

void PatronSinusoidal::generarPatronSinusoidalHorizontal(int rows, int cols) {
	Patron::matriz = new Mat(rows, cols, CV_8UC3);
	double value;

	for (int i = 0; i < cols; i++) {
		for (double j = 0; j < rows; j++) {
			value = getCosValue(j);
			matriz->row(j).col(i) = Scalar(value, value, value);
		}
	}
}

double PatronSinusoidal::getCosValue(double j) {
	return (1 + cos((w / periodo) * j + phi0))*255/2;
}

