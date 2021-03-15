#include <iostream>
#include "Patron.h"

#ifndef PATRON_COLOR_H
#define PATRON_COLOR_H

using namespace std;

class PatronColor : public Patron
{
public:
	PatronColor(int r, int g, int b);
};

#endif
