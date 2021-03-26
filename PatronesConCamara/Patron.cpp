#include "Patron.h"

void Patron::cargarPatronBitmap(HWND hwnd, Pantalla* pantalla) {

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	HDC hdcMem;

	hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, bitmap);
	//StretchBlt(hdc, 0, 0, 1600, 900, hdcMem, 0, 0, Patron::matriz.cols, Patron::matriz.rows, SRCCOPY); //https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-stretchblt
	BitBlt(hdc, 0, 0, pantalla->getWidth(), pantalla->getWidth(), hdcMem, 0, 0, SRCCOPY);
	DeleteDC(hdcMem);

	EndPaint(hwnd, &ps);
}

auto Patron::matToBmp(Mat frame) -> HBITMAP
{
	auto convertOpenCVBitDepthToBits = [](const int32_t value)
	{
		auto regular = 0u;

		switch (value)
		{
		case CV_8U:
		case CV_8S:
			regular = 8u;
			break;

		case CV_16U:
		case CV_16S:
			regular = 16u;
			break;

		case CV_32S:
		case CV_32F:
			regular = 32u;
			break;

		case CV_64F:
			regular = 64u;
			break;

		default:
			regular = 0u;
			break;
		}

		return regular;
	};

	auto imageSize = frame.size();
	assert(imageSize.width && "invalid size provided by frame");
	assert(imageSize.height && "invalid size provided by frame");

	if (imageSize.width && imageSize.height)
	{
		auto headerInfo = BITMAPINFOHEADER{};
		ZeroMemory(&headerInfo, sizeof(headerInfo));

		headerInfo.biSize = sizeof(headerInfo);
		headerInfo.biWidth = imageSize.width;
		headerInfo.biHeight = -(imageSize.height); // negative otherwise it will be upsidedown
		headerInfo.biPlanes = 1;// must be set to 1 as per documentation frame.channels();

		const auto bits = convertOpenCVBitDepthToBits(frame.depth());
		headerInfo.biBitCount = frame.channels() * bits;

		auto bitmapInfo = BITMAPINFO{};
		ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));

		bitmapInfo.bmiHeader = headerInfo;
		bitmapInfo.bmiColors->rgbBlue = 0;
		bitmapInfo.bmiColors->rgbGreen = 0;
		bitmapInfo.bmiColors->rgbRed = 0;
		bitmapInfo.bmiColors->rgbReserved = 0;

		auto dc = GetDC(nullptr);
		assert(dc != nullptr && "Failure to get DC");
		auto bmp = CreateDIBitmap(dc,
			&headerInfo,
			CBM_INIT,
			frame.data,
			&bitmapInfo,
			DIB_RGB_COLORS);
		assert(bmp != nullptr && "Failure creating bitmap from captured frame");

		return bmp;
	}
	else
	{
		return nullptr;
	}
}

Scalar Patron::getColor(int indexColor, double intensidad) {
	switch (indexColor) {
	case 0:
		return Scalar(intensidad, intensidad, intensidad);
		break;
	case 1:
		return Scalar(0, 0, intensidad);
		break;
	case 2:
		return Scalar(0, intensidad, 0);
		break;
	case 3:
	default:
		return Scalar(intensidad, 0, 0);
		break;
	}
}