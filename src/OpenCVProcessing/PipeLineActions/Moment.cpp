/** @file		Moment.cpp
 *  @brief		C++ file of the Moment child-class
 *  @details	Contains the implementation code Moment child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLinecpp
 */
#include "Moment.h"
using namespace std;
using namespace cv;

Moment::Moment(const cv::String name) : PipeLineAction(name)
{
	Moments m = Moments();
	Point center = Point(0, 0);
	area = 50;
	areaMax = 1000;
}

void Moment::setAction(void* data)
{
	vector<vector<Point>>* d = static_cast<vector<vector<Point>>*>(data);
	if (!d->empty()) {
		m = moments((*d)[(*d).size() - 1], false);
		center = Point(m.m10 / m.m00, m.m01 / m.m00);
	}
	else {
		center = Point(-10, -10);
	}
}

void* Moment::getAction()
{
	return &center;
}

Point* Moment::getCenterOfMass()
{
	return &center;
}

void Moment::showWindow()
{
	show = false;
}