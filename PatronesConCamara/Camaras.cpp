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

void Camaras::inicializarTodasLasCamaras() {
	for (int i = 0; i < devMgr.deviceCount(); i++) {
		Camara* camara = new Camara(i, devMgr);
		camara->initializeDevice();
		listaDispositivos.emplace_back(camara);
	}
}

void Camaras::guardarImagenesEnDisco(string path, string relativePath, string extension, int num) {
	list<thread> threads = {};
	for (auto const& camara : listaDispositivos) {
		threads.emplace_back(thread(&Camaras::ejecutarHiloDisco, this, camara, path, relativePath, extension, num));
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

void Camaras::getImages(int n) {
	list<thread> threads = {};
	for (auto const& camara : listaDispositivos) {
		threads.emplace_back(thread(&Camaras::ejecutarHiloImagenes, this, camara, n));
	}
	for (auto& thread : threads) {
		thread.join();
	}
}

void Camaras::ejecutarHiloDisco(Camara* camara, string path, string relativePath, string extension, int num) {
	camara->guardarImagenEnDisco(path, relativePath, extension, num);
}

void Camaras::ejecutarHiloImagenes(Camara* camara, int num) {
	camara->getImage(num);
}

Camara* Camaras::getCamara(int index) {

	auto it = listaDispositivos.begin();
	std::advance(it, index);

	return *it;
}

DeviceManager Camaras::getManager() {
	return devMgr;
}