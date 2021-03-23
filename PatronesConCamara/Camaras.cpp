#include "Camaras.h"

Camaras::Camaras() {
	Camaras::devMgr;

	// Cuenta la cantidad de dispositivos (cámaras) disponibles.
	if (devMgr.deviceCount() == 0)
	{
		cout << "No device found! Unable to continue!" << endl;
		cin.get();
	}
}

void Camaras::inicializarCamara(int index) {
	Camara* camara = new Camara(index, devMgr);
	camara->initializeDevice();
	listaDispositivos.emplace_back(camara);
}

Camara* Camaras::getCamara(int index) {

	auto it = listaDispositivos.begin();
	std::advance(it, index);

	return *it;
}

DeviceManager Camaras::getManager() {
	return devMgr;
}