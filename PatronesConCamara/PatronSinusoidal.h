#include <iostream>
#include "Patron.h"

#ifndef PATRON_SINUSOIDAL_H
#define PATRON_SINUSOIDAL_H

#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3

#define VERTICAL 0
#define HORIZONTAL 1

using namespace std;

class PatronSinusoidal : public Patron
{
public:
	double phi0;
	double periodo;
	double w;
	PatronSinusoidal(int indexPatron, int indexColor, double phi0, double periodo, int rows, int cols);
	void generarPatronSinusoidalVertical(int rows, int cols, int indexColor);
	void generarPatronSinusoidalHorizontal(int rows, int cols, int indexColor);
	Scalar getColor(int indexColor, double value);
	double getCosValue(double j);
};

#endif