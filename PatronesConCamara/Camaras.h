#include <mvIMPACT_acquire_GenICam.h>
#include <mvIMPACT_acquire.h>
#include <mvIMPACT_acquire_helper.h>
#include <iostream>
#include <list>
#include <thread>
#include "Camara.h"
#include "MyBarrier.h"

#ifndef CAMARAS_H
#define CAMARAS_H

using namespace std;
using namespace mvIMPACT::acquire;

class Camaras
{
public:
	DeviceManager devMgr;
	list<Camara*> listaDispositivos;

	Camaras();
	void inicializarCamara(int index);
	void inicializarTodasLasCamaras();
	Camara* getCamara(int index);
	void guardarImagenesEnDisco(string path, string relativePath, string extension, int num);
	void ejecutarHiloDisco(Camara* camara, string path, string relativePath, string extension, int num);
	void ejecutarHiloImagenes(Camara* camara, int num);
	DeviceManager getManager();
	void getImages(int n);
};

#endif
