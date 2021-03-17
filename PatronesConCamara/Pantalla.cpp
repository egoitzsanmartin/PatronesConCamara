#include "Pantalla.h"

Pantalla::Pantalla(HINSTANCE hInstance, string className) {

	//Step 1: Registering the Window Class    ----->    http://www.winprog.org/tutorial/simple_window.html
	Pantalla::hInstance = hInstance;
	Pantalla::className = className;

	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	Pantalla::width = desktop.right;
	Pantalla::height = desktop.bottom;
}

int Pantalla::crearVentana(string className) {
	char *str = new char[className.length() + 1];
	strcpy_s(str, className.length() + 1, className.c_str());

	hwnd = CreateWindowEx(
		0,
		str,
		"The title of my window",
		WS_POPUP | WS_VISIBLE,
		0, 0, Pantalla::width, Pantalla::height,   //X-position, Y-position, width, height
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	return 1;
}

void Pantalla::borrarImagen() {
	InvalidateRect(hwnd, NULL, FALSE);
}

HINSTANCE Pantalla::getHInstance() {
	return hInstance;
}

HWND Pantalla::getHwnd() {
	return hwnd;
}

string Pantalla::getClassName() {
	return className;
}

int Pantalla::getWidth() {
	return width;
}

int Pantalla::getHeight() {
	return height;
}