#define _CRT_SECURE_NO_WARNINGS

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <chrono>
#include <ctime>
#include <iomanip>
#include <time.h>
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
		camara->cambiarTiempoDeExposicion(300000);
		camara->cambiarAGrayscale();
		camara->cambiarGanancia(6);
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

	bool end = false;
	thread keyWait(waitForKeyThread, &end);
	int repeticiones = 0;
	string path;
	//chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
	//time_t now_c = chrono::system_clock::to_time_t(now);
	//string now_string = to_string(now_c);
	string time = getTimestamp();

	while (true) {	
		for (auto const& secuencia : secuencias) {
			path = ROOT_PATH + "-" + time + "-" + to_string(repeticiones);
			secuencia->ejecutarSecuencia(pantalla, camara, path, EXTENSION, ENABLE_CAMERA);
		}
		repeticiones++;
		if (end) {
			break;
		}
	}
	
	keyWait.join();

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