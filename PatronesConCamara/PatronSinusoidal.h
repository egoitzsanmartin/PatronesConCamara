#include <iostream>
#include "Patron.h"

#ifndef PATRON_SINUSOIDAL_H
#define PATRON_SINUSOIDAL_H

using namespace std;

class PatronSinusoidal : public Patron
{
public:
	double phi0;
	double periodo;
	double w;
	PatronSinusoidal(int indexPatron, int indexColor, int phi0, int periodo, int rows, int cols);
	void generarPatronSinusoidalVertical(int rows, int cols);
	void generarPatronSinusoidalHorizontal(int rows, int cols);
	double getCosValue(double j);
};

#endif