#include <iostream>
#include <windows.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "Pantalla.h"

#ifndef PATRON_H
#define PATRON_H

using namespace std;
using namespace cv;

class Patron
{
public:
	HBITMAP bitmap;
	Mat* matriz;
	void cargarPatronBitmap(HWND hwnd, Pantalla* pantalla);
	auto matToBmp(Mat frame) -> HBITMAP;
	Scalar getColor(int indexColor, double intensidad);
};

#endif
