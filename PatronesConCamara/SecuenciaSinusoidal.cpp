#include "SecuenciaSinusoidal.h"

SecuenciaSinusoidal::SecuenciaSinusoidal(int indexPatron, int indexColor, double periodo, Pantalla* pantalla, int n) {
	Secuencia::n = n;
	double phi0 = (2 * (atan(1) * 4) / n) * 0;
	Secuencia::patrones = new Patron*[n];

	for (int i = 0; i < n; i++) {
		patrones[i] = new PatronSinusoidal(indexPatron, indexColor, phi0, periodo, pantalla->getHeight(), pantalla->getWidth());
		phi0 = (2 * (atan(1) * 4) / n) * i;
	}
}
