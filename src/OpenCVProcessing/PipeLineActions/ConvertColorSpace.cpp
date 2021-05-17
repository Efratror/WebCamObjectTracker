/** @file		ConvertColorSpace.cpp
 *  @brief		C++ file of the ConvertColorSpace child-class
 *  @details	Contains the implementation code ConvertColorSpace child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLinecpp
 */
#include "ConvertColorSpace.h"

using namespace std;
using namespace cv;

ConvertColorSpace::ConvertColorSpace(const cv::String name) : PipeLineAction(name){}

void ConvertColorSpace::setAction(void* data)
{
	Mat* d = static_cast<Mat*>(data);
	cvtColor(*d, img, COLOR_BGR2HSV);
}

void ConvertColorSpace::showWindow()
{
	if (!show) {
		namedWindow(name);
		show = true;
	}
	imshow(name, img);
}