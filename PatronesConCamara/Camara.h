#include <mvIMPACT_acquire_GenICam.h>
#include <mvIMPACT_acquire.h>
#include <mvIMPACT_acquire_helper.h>
#include <exampleHelper.h>
#include <vector>
#include <list>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <direct.h>
#include <windows.h>

#ifndef CAMARA_H
#define CAMARA_H

using namespace std;
using namespace cv;
using namespace mvIMPACT::acquire;

class Camara
{
private:
	int getDataType(TImageBufferPixelFormat format);
	bool isDeviceSupportedBySample(const Device* const pDev);
public:
	list<Mat> imagenes;
	DeviceManager devMgr;
	Device* pDev;
	int index;

	Camara(int index, DeviceManager devMgr);
	void getImage(int n);
	Device* getPDev();
	Device* initializeDevice();
	void guardarImagenEnDisco(string path, string relativePath, string extension, int num);
	void cambiarTiempoDeExposicion(int tiempo);
	void cambiarGanancia(int ganancia);
	void cambiarAGrayscale();
	void createDirectory(string path);
	int getIndex();

};

#endif
