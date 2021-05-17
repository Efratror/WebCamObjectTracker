/** @file		Contour.cpp
 *  @brief		C++ file of the Contour child-class
 *  @details	Contains the implementation code Contour child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLinecpp
 */
#include "Contour.h"
using namespace std;
using namespace cv;

Contour::Contour(const cv::String name) : PipeLineAction(name)
{
	accuracy = 3;
	area = 10;
}

void Contour::setAction(void* data)
{
	Mat* d = static_cast<Mat*>(data);
	// Find Contours
	img = Mat(d->rows, d->cols, CV_8SC3);
	findContours(d->clone(), contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
		
	if (contours.size() > 0) {
		//Draw contours
		polylines.resize(contours.size());
		bool areaBigEnough = false;
		Scalar lineColor;
		for (size_t i = 0; i < contours.size(); i++)
		{

			approxPolyDP(contours[i], polylines[i], accuracy, true);
			//Check area size
			if (contourArea(contours[i]) > area*100) {
				areaBigEnough = true;
				lineColor = green;
			}
			else {
				lineColor = red;
			}
			drawContours(img, polylines, (int)i, lineColor);
		}
		//Sort contours by size
		if (areaBigEnough) {
			sort(
				contours.begin(),
				contours.end(),
				[](const vector<Point>& a, const vector<Point>& b) { return a.size() < b.size(); }
			);
		}
		// Clear contour area
		else {
			contours.clear();
		}
	}
}

void* Contour::getAction()
{
	return &contours;
}

void Contour::showWindow()
{
	if (!show) {
		namedWindow(name);
		createTrackbar("Accuracy", name, &accuracy, accuracyMax);
		createTrackbar("Area factor", name, &area, areaMax);
		show = true;
	}
	imshow(name, img);
}