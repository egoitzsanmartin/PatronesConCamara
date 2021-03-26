#include "PatronColor.h"

PatronColor::PatronColor(int indexColor, double intensidad, int rows, int cols) {
	Patron::matriz = new Mat(rows, cols, CV_8UC3);

	for (double i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			matriz->row(j).col(i) = getColor(indexColor, intensidad);
		}
	}

	bitmap = matToBmp(*matriz);
}