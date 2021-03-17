#include <mvIMPACT_acquire_GenICam.h>
#include <mvIMPACT_acquire.h>
#include <mvIMPACT_acquire_helper.h>
#include <exampleHelper.h>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#ifndef CAMARA_H
#define CAMARA_H

using namespace std;
using namespace cv;
using namespace mvIMPACT::acquire;

bool isDeviceSupportedBySample(const Device* const pDev);

class Camara
{
private:
	int getDataType(TImageBufferPixelFormat format);
	
public:
	Device* pDev;
	int index;

	Camara(int index);
	Mat getImage(DeviceManager devMgr);
	Device* getPDev();
	Device* initializeDevice(DeviceManager devMgr);
	void guardarImagenEnDisco(string path, string extension, int num, Mat imagen);
	void cambiarTiempoDeExposicion(int tiempo, DeviceManager devMgr);
};

#endif
