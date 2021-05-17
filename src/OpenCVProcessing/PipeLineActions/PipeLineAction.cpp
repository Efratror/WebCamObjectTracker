/** @file		PipeLineAction.cpp
 *  @brief		C++ file of the PipeLineAction base-class
 *  @details	Contains the implementation code PipeLineAction base-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	pipeLinecpp
 */
#include "PipeLineAction.h"

PipeLineAction::PipeLineAction()
{
	img = cv::Mat::zeros(cv::Size(1, 1), CV_8SC3);
	show = false;
	this->name = "";
}

PipeLineAction::PipeLineAction(const cv::String name)
{
	img = cv::Mat::zeros(cv::Size(1, 1), CV_8SC3);
	show = false;
	this->name = name;
}

void* PipeLineAction::getAction()
{
	return &img;
}

void PipeLineAction::hideWindow()
{
	if (show) {
		cv::destroyWindow(name);
		show = false;
	}
}

cv::String PipeLineAction::getName()
{
	return name;
}
