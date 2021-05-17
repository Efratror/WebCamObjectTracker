/** @file		Blur.cpp
 *  @brief		C++ file of the Blur child-class
 *  @details	Contains the implementation code Blur child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLinecpp
 */
#include "Blur.h"

using namespace std;
using namespace cv;

Blur::Blur(const cv::String name) : PipeLineAction(name)
{
	slider = 3;
	kernelSize = 2 * slider + 1;
	sigma = 0.3 * ((static_cast<float>(kernelSize) - 1) * 0.5 - 1) + 0.8;
}

void Blur::setAction(void* data)
{
	Mat* d = static_cast<Mat*>(data);
	GaussianBlur(*d, img, Size(kernelSize, kernelSize), sigma);
}

void Blur::showWindow()
{
	if (!show) {
		namedWindow(name);
		createTrackbar("Factor", name, &slider, maxValue, onChange, this);
		show = true;
	}
	imshow(name, img);
}

void Blur::onChange(int, void* data)
{
	Blur* b = static_cast<Blur*>(data);
	if (b) {
		b->kernelSize = 2 * b->slider + 1;
		b->sigma = 0.3 * ((static_cast<float>(b->kernelSize) - 1) * 0.5 - 1) + 0.8;
	}
}