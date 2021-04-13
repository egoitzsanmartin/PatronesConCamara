#include <mvIMPACT_acquire_GenICam.h>
#include <mvIMPACT_acquire.h>
#include <mvIMPACT_acquire_helper.h>
#include <exampleHelper.h>
#include <vector>
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
	
public:
	DeviceManager devMgr;
	Device* pDev;
	int index;

	Camara(int index, DeviceManager devMgr);
	Mat getImage();
	Device* getPDev();
	Device* initializeDevice();
	void guardarImagenEnDisco(string path, string relativePath, string extension, int cameraIndex, int num, Mat imagen);
	void cambiarTiempoDeExposicion(int tiempo);
	void cambiarGanancia(int ganancia);
	void cambiarAGrayscale();
	bool isDeviceSupportedBySample(const Device* const pDev);
	void createDirectory(string path);

};

#endif
