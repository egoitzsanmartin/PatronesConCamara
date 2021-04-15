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
	void ejecutarHilo(Camara* camara, string path, string relativePath, string extension, int num, MyBarrier* barrera);
	DeviceManager getManager();
};

#endif
