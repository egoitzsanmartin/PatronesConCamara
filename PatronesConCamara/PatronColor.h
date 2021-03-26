#include <iostream>
#include "Patron.h"

#ifndef PATRON_COLOR_H
#define PATRON_COLOR_H

#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3

using namespace std;

class PatronColor : public Patron
{
public:
	PatronColor(int indexColor, double intensidad, int rows, int cols);
};

#endif
