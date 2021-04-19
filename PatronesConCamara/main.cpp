#define _CRT_SECURE_NO_WARNINGS

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "Patron.h"
#include "PatronColor.h"
#include "PatronSinusoidal.h"
#include "Pantalla.h"
#include "InicializarPantalla.h"
#include "Camara.h"
#include "Camaras.h"
#include "Secuencia.h"
#include "SecuenciaSinusoidal.h"
#include "SecuenciaColor.h"

static const string ROOT_PATH = "C:/Users/Aita/Documents/exp";
static const string CONFIG_PATH = "C:/Users/Aita/Documents/config.txt";
static const string EXTENSION = ".bmp";
static const bool ENABLE_CAMERA = true;
static const string CLASS_NAME = "myWindowClass";

vector<vector<string>> leerFichero();
void waitForKeyThread(bool* end);
string getTimestamp();
string crearPath(int repeticiones, string time);
vector<Secuencia*> generarPatrones(Pantalla* pantalla);

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	registrarVentana(hInstance, CLASS_NAME);
	Pantalla* pantalla = new Pantalla(hInstance, CLASS_NAME);
	pantalla->crearVentana(CLASS_NAME);

	Camaras* camaras = NULL;

	if (ENABLE_CAMERA) {
		Camara* camara1 = NULL;
		camaras = new Camaras();
		camaras->inicializarTodasLasCamaras();

		camara1 = camaras->getCamara(0);
		camara1->cambiarTiempoDeExposicion(30000);
		camara1->cambiarAGrayscale();
		camara1->cambiarGanancia(4);
	}
	vector<Secuencia*> secuencias = generarPatrones(pantalla);
	bool end = false;
	thread keyWait(waitForKeyThread, &end);
	int repeticiones = 0;
	string path;
	string time = getTimestamp();

	while (true) {
		for (auto const& secuencia : secuencias) {
			path = crearPath(repeticiones, time);
			secuencia->ejecutarSecuencia(pantalla, camaras, path, EXTENSION, ENABLE_CAMERA);
		}
		repeticiones++;

		if (end) {
			break;
		}
	}
	
	keyWait.join();

	return 0;
}

string crearPath(int repeticiones, string time) {
	return ROOT_PATH + "-" + time + "-" + to_string(repeticiones);
}

vector<vector<string>> leerFichero() {

	string token;
	string line;
	vector<vector<string>> lines;
	vector<string> parameters;
	ifstream input;
	string delimiter = "$";
	input.open(CONFIG_PATH);

	if (!input.is_open()) {
		return lines;
	}

	while (input) {
		size_t pos = 0;
		getline(input, line);

		while ((pos = line.find(delimiter)) != string::npos) {
			token = line.substr(0, pos);
			parameters.push_back(token);
			line.erase(0, pos + delimiter.length());
		}

		lines.push_back(parameters);
		parameters.clear();

		input >> ws;

		if (!input) {
			break;
		}
	}

	input.close();

	return lines;
}

void waitForKeyThread(bool* end) {
	cout << "Press [INTRO] to end the program: ";
	getchar();
	*end = true;
	cout << endl << "Waiting for sequence to end... ";
}

string getTimestamp() {
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	char mes[2];
	char dia[2];
	char h[2];
	char m[2];
	char s[2];

	sprintf_s(mes, 10, "%02d", tm.tm_mon + 1);
	sprintf_s(dia, 10, "%02d", tm.tm_mday);
	sprintf_s(h, 10, "%02d", tm.tm_hour);
	sprintf_s(m, 10, "%02d", tm.tm_min);
	sprintf_s(s, 10, "%02d", tm.tm_sec);

	string mesString = mes;
	string diaString = dia;
	string hString = h;
	string mString = m;
	string sString = s;

	string now_string = to_string(tm.tm_year + 1900) + "." + mesString + "." + diaString + "-" + hString + "." + mString + "." + sString;

	return now_string;
}

vector<Secuencia*> generarPatrones(Pantalla* pantalla) {

	vector<vector<string>> lines = leerFichero();
	vector<Secuencia*> secuencias;
	for (auto const& line : lines) {
		int color;

		if (line.at(0) == "SINUSOIDAL") {
			int orientacion;

			if (line.at(1) == "V") {
				orientacion = VERTICAL;
			}
			else if (line.at(1) == "H") {
				orientacion = HORIZONTAL;
			}

			if (line.at(2) == "R") {
				color = RED;
			}
			else if (line.at(2) == "G") {
				color = GREEN;
			}
			else if (line.at(2) == "B") {
				color = BLUE;
			}
			else if (line.at(2) == "W") {
				color = WHITE;
			}

			secuencias.push_back(new SecuenciaSinusoidal(orientacion, color, stoi(line.at(3)), stoi(line.at(4)), pantalla));
		}
		else if (line.at(0) == "COLOR") {

			if (line.at(1) == "R") {
				color = RED;
			}
			else if (line.at(1) == "G") {
				color = GREEN;
			}
			else if (line.at(1) == "B") {
				color = BLUE;
			}
			else if (line.at(1) == "W") {
				color = WHITE;
			}

			secuencias.push_back(new SecuenciaColor(color, stoi(line.at(2)), stoi(line.at(3)), stoi(line.at(4)), pantalla));
		}
	}

	return secuencias;
}