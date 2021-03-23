#include "Pantalla.h"

Pantalla::Pantalla(HINSTANCE hInstance, string className) {

	// Utiliza dos puntos, uno para recoger los posibles monitores de arriba e izquierda, y otro
	// para los posibles monitores de debajo y derecha.
	Pantalla::hInstance = hInstance;
	Pantalla::className = className;

	HMONITOR hMonitor1;
	HMONITOR hMonitor2;
	MONITORINFO mi1;
	MONITORINFO mi2;

	RECT option1, option2;

	POINT pt1 = { -4000, -2000 };
	POINT pt2 = { 4000, 2000 };

	// Monitores encima y a la izquierda del principal {0,0}
	hMonitor1 = MonitorFromPoint(pt1, MONITOR_DEFAULTTONEAREST);
	mi1.cbSize = sizeof(mi1);
	GetMonitorInfo(hMonitor1, &mi1);

	// Monitores debajo y a la derecha del principal {0,0}
	hMonitor2 = MonitorFromPoint(pt2, MONITOR_DEFAULTTONEAREST);
	mi2.cbSize = sizeof(mi2);
	GetMonitorInfo(hMonitor2, &mi2);

	option1 = mi1.rcMonitor;
	option2 = mi2.rcMonitor;

	if (mi1.dwFlags != MONITORINFOF_PRIMARY) {
		Pantalla::width = option1.right - option1.left;
		Pantalla::height = option1.bottom - option1.top;
		Pantalla::x = option1.left;
		Pantalla::y = option1.top;
	}else if (mi2.dwFlags != MONITORINFOF_PRIMARY) {
		Pantalla::width = option2.right - option2.left;
		Pantalla::height = option2.bottom - option2.top;
		Pantalla::x = option2.left;
		Pantalla::y = option2.top;
	}else {
		cout << "Display Monitor not found." << endl;
		/*Pantalla::width = option1.right - option1.left;     //  
		Pantalla::height = option1.bottom - option1.top;	  // Descomentar solo para desarrollo
		Pantalla::x = option1.left;							  //
		Pantalla::y = option1.top;*/						  //
	}
}

int Pantalla::crearVentana(string className) {
	char *str = new char[className.length() + 1];
	strcpy_s(str, className.length() + 1, className.c_str());

	Pantalla::hwnd = CreateWindowEx(
		0,
		str,
		"The title of my window",
		WS_POPUP | WS_VISIBLE,
		Pantalla::x, Pantalla::y, Pantalla::width, Pantalla::height,   //X-position, Y-position, width, height
		NULL, NULL, hInstance, NULL);

	if (Pantalla::hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(Pantalla::hwnd, SW_SHOWNORMAL);
	UpdateWindow(Pantalla::hwnd);

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