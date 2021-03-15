#include <mvIMPACT_acquire_GenICam.h>
#include <mvIMPACT_acquire.h>
#include <mvIMPACT_acquire_helper.h>
#include <iostream>
#include <list>
#include "Camara.h"

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
	Camara* getCamara(int index);
	DeviceManager getManager();
};

#endif
