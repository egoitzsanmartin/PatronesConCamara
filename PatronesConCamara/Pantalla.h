#include <iostream>
#include <windows.h>

#ifndef PANTALLA_H
#define PANTALLA_H

using namespace std;

class Pantalla
{
private:	
	HWND hwnd;
	HINSTANCE hInstance;
	string className;
	int x;
	int y;
	int width;
	int height;

public:
	Pantalla(HINSTANCE hInstance, string className);
	int crearVentana(string className);
	void Pantalla::borrarImagen();
	HINSTANCE Pantalla::getHInstance();
	HWND Pantalla::getHwnd();
	string Pantalla::getClassName();
	int Pantalla::getHeight();
	int Pantalla::getWidth();
};

#endif