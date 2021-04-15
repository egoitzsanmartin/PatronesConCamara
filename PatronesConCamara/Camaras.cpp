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
	MyBarrier* barrera = new MyBarrier(listaDispositivos.size());
	list<thread> threads = {};
	for (auto const& camara : listaDispositivos) {
		threads.emplace_back(thread(&Camaras::ejecutarHilo, this, camara, path, relativePath, extension, num, barrera));
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

void Camaras::ejecutarHilo(Camara* camara, string path, string relativePath, string extension, int num, MyBarrier* barrera) {
	camara->guardarImagenEnDisco(path, relativePath, extension, camara->getIndex(), num, camara->getImage());
	barrera->wait();
}

Camara* Camaras::getCamara(int index) {

	auto it = listaDispositivos.begin();
	std::advance(it, index);

	return *it;
}

DeviceManager Camaras::getManager() {
	return devMgr;
}