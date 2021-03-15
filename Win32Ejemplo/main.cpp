#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>
#include <cstddef>
#include <math.h>

using namespace cv;
using namespace std;

int rows = 900;
int cols = 1600;

int main() {
	double w = 2 * atan(1)*4 * 500;
	double phi0 = 0;
	Mat matriz(rows, cols, CV_8UC3);

	for (int i = 0; i < cols; i++)
	{
		for (float j = 0; j < rows; j++){
			matriz.row(j).col(i) = Scalar(0, abs(cos(w*(j/44100) + phi0)) * 255, 0);
		}
	}

	namedWindow("Display window", WINDOW_NORMAL);
	imshow("Display window", matriz);
	waitKey(0);

}