#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
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

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

static const string PATH = "C:/Users/Aita/Documents/experimento";
static const string CONFIG_PATH = "C:/Users/Aita/Documents/experimento/config/config.txt";
static const string EXTENSION = ".bmp";
static const bool ENABLE_CAMERA = false;
static const string CLASS_NAME = "myWindowClass";
static const int N = 100;

vector<vector<string>> leerFichero();

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	registrarVentana(hInstance, CLASS_NAME);
	Pantalla* pantalla = new Pantalla(hInstance, CLASS_NAME);
	pantalla->crearVentana(CLASS_NAME);

	Camaras* camaras = NULL;
	Camara* camara = NULL;

	if (ENABLE_CAMERA) {
		camaras = new Camaras();
		camaras->inicializarCamara(0);
		camara = camaras->getCamara(0);
		camara->cambiarTiempoDeExposicion(30000);
	}

	vector<vector<string>> lines = leerFichero();
	vector<Secuencia*> secuencias;
	for (auto const& line : lines) {
		int color;

		if (line.at(0) == "SINUSOIDAL") {
			int orientacion;

			if (line.at(1) == "V") {
				orientacion = VERTICAL;
			}
			else if(line.at(1) == "H"){
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

	for (auto const& secuencia : secuencias) {
		secuencia->ejecutarSecuencia(pantalla, camara, PATH, EXTENSION, ENABLE_CAMERA);
	}

	return 0;
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