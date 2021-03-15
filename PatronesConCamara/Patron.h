#include <iostream>
#include <windows.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#ifndef PATRON_H
#define PATRON_H

using namespace std;
using namespace cv;

class Patron
{
public:
	HBRUSH brush;
	HBITMAP bitmap;
	Mat* matriz;
	void cargarPatron(HWND hwnd);
	void cargarPatronBitmap(HWND hwnd, int width, int height);
	auto matToBmp(Mat frame) -> HBITMAP;
	HBRUSH getBrush();
};

#endif
