#include <iostream>
#include <windows.h>
#include <string>
#include "PatronColor.h"

using namespace std;

#ifndef INICIALIZAR_PANTALLA_H
#define INICIALIZAR_PANTALLA_H

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int registrarVentana(HINSTANCE hInstance, string className);

#endif