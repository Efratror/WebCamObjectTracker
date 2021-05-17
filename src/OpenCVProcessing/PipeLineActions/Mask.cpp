/** @file		Mask.cpp
 *  @brief		C++ file of the Mask child-class
 *  @details	Contains the implementation code Mask child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLinecpp
 */
#include "Mask.h"

using namespace std;
using namespace cv;

Mask::Mask(const cv::String name) : PipeLineAction(name)
{
	lowH = 0, lowS = 0, lowV = 0;
	highH = maxValueH, highS = maxValue, highV = maxValue;

	pixelSize = 2;
}

Mask::Mask(const cv::String name, HSV_MASK_VALUES hsvValues) : PipeLineAction(name)
{
	this->lowH = hsvValues.lowH;
	this->lowS = hsvValues.lowS;
	this->lowV = hsvValues.lowV;
	this->highH = hsvValues.highH;
	this->highS = hsvValues.highS;
	this->highV = hsvValues.highV;

	pixelSize = 2;
}

void Mask::setAction(void* data)
{
	Mat* d = static_cast<Mat*>(data);
	inRange(*d,
		Scalar(lowH, lowS, lowV),
		Scalar(highH, highS, highV),
		img);
	erode(img, img, pixelSize);
	dilate(img, img, pixelSize);
}

void Mask::showWindow()
{
	if (!show) {
		namedWindow(name);
		createTrackbar("Low H", name, &lowH, maxValueH, onLowHTreshTrackbar, this);
		createTrackbar("High H", name, &highH, maxValueH, onHighHTreshTrackbar, this);
		createTrackbar("Low S", name, &lowS, maxValue, onLowSTreshTrackbar, this);
		createTrackbar("High S", name, &highS, maxValue, onHighSTreshTrackbar, this);
		createTrackbar("Low V", name, &lowV, maxValue, onLowVTreshTrackbar, this);
		createTrackbar("High V", name, &highV, maxValue, onHighVTreshTrackbar, this);
		createTrackbar("Pixel size", name, &pixelSize, maxValuePixel, onHighVTreshTrackbar, this);
		show = true;
	}
	imshow(name, img);
}

void Mask::onLowHTreshTrackbar(int, void* data)
{
	Mask* m = static_cast<Mask*>(data);
	m->lowH = min(m->highH - 1, m->lowH);
	setTrackbarPos("Low H", m->name, m->lowH);
}

void Mask::onHighHTreshTrackbar(int, void* data)
{
	Mask* m = static_cast<Mask*>(data);
	m->highH = max(m->highH, m->lowH + 1);
	setTrackbarPos("High H", m->name, m->highH);
}

void Mask::onLowSTreshTrackbar(int, void* data)
{
	Mask* m = static_cast<Mask*>(data);
	m->lowS = min(m->highS - 1, m->lowS);
	setTrackbarPos("Low S", m->name, m->lowS);
}

void Mask::onHighSTreshTrackbar(int, void* data)
{
	Mask* m = static_cast<Mask*>(data);
	m->highS = max(m->highS, m->lowS + 1);
	setTrackbarPos("High S", m->name, m->highS);
}

void Mask::onLowVTreshTrackbar(int, void* data)
{
	Mask* m = static_cast<Mask*>(data);
	m->lowV = min(m->highV - 1, m->lowV);
	setTrackbarPos("Low V", m->name, m->lowV);
}

void Mask::onHighVTreshTrackbar(int, void* data)
{
	Mask* m = static_cast<Mask*>(data);
	m->highV = max(m->highV, m->lowV + 1);
	setTrackbarPos("High V", m->name, m->highV);
}