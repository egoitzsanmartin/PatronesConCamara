#include "Camara.h"

Camara::Camara(int index){
	Camara::index = index;
}

Device* Camara::initializeDevice(DeviceManager devMgr) {

	pDev = devMgr.getDevice(index);

	if (pDev == nullptr)
	{
		cout << "Unable to continue! Press [ENTER] to end the application" << endl;
		cin.get();
	}
	try
	{
		cout << "Initialising the device. This might take some time..." << endl << endl;
		pDev->interfaceLayout.write(dilGenICam); // This is also done 'silently' by the 'getDeviceFromUserInput' function but your application needs to do this as well so state this here clearly!
		pDev->open();
		cout << "Device open" << endl << endl;
	}
	catch (const ImpactAcquireException& e)
	{
		// this e.g. might happen if the same device is already opened in another process...
		cout << "An error occurred while opening device " << pDev->serial.read()
			<< "(error code: " << e.getErrorCodeAsString() << ")." << endl
			<< "Press [ENTER] to end the application..." << endl;
		cin.get();
	}

	GenICam::AcquisitionControl ac(pDev);

	// "On" para activar el sistema de trigger. "Off" para captura continua.
	ac.triggerMode.writeS("Off");

	return pDev;
}


Mat Camara::getImage(DeviceManager devMgr) {
	pDev = devMgr.getDevice(index);
	helper::RequestProvider requestProvider(pDev);
	requestProvider.acquisitionStart();
	shared_ptr<Request> pRequest = requestProvider.waitForNextRequest();

	int dataType = getDataType(pRequest->imagePixelFormat.read());
	Mat matriz;
	matriz = Mat(Size(pRequest->imageWidth.read(), pRequest->imageHeight.read()), dataType, pRequest->imageData.read(), pRequest->imageLinePitch.read()).clone();
	requestProvider.acquisitionStop();

	return matriz;
}

Device* Camara::getPDev() {
	return pDev;
}

//No se puede definir en el .h
bool isDeviceSupportedBySample(const Device* const pDev)
//-----------------------------------------------------------------------------
{
	if (!pDev->interfaceLayout.isValid() &&
		!pDev->acquisitionStartStopBehaviour.isValid())
	{
		return false;
	}

	vector<TDeviceInterfaceLayout> availableInterfaceLayouts;
	pDev->interfaceLayout.getTranslationDictValues(availableInterfaceLayouts);
	return find(availableInterfaceLayouts.begin(), availableInterfaceLayouts.end(), dilGenICam) != availableInterfaceLayouts.end();
}

int Camara::getDataType(TImageBufferPixelFormat format) {
	int dataType;
	switch (format) {
	case ibpfMono8:
		dataType = CV_8UC1;
		break;
	case ibpfMono10:
	case ibpfMono12:
	case ibpfMono14:
	case ibpfMono16:
		dataType = CV_16UC1;
		break;
	case ibpfMono32:
		dataType = CV_32SC1;
		break;
	case ibpfBGR888Packed:
	case ibpfRGB888Packed:
		dataType = CV_8UC3;
		break;
	case ibpfRGBx888Packed:
		dataType = CV_8UC4;
		break;
	case ibpfRGB101010Packed:
	case ibpfRGB121212Packed:
	case ibpfRGB141414Packed:
	case ibpfRGB161616Packed:
		dataType = CV_16UC3;
		break;
	}
	return dataType;
}

void Camara::guardarImagenEnDisco(string path, string extension, int num, Mat imagen) {
	string imageNumber = to_string(num);
	imwrite(path + "/img" + imageNumber + extension, imagen);
}