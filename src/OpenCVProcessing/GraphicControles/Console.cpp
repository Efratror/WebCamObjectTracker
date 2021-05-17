/** @file		Console.cpp
 *  @brief		C++ file of the Console class
 *  @details	Contains the implementation code Console class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup graphiccpp
 */
#include "Console.h"

using namespace cv;

Scalar Console::messageColor(std::string str)
{

	if (0 == strncmp("ERROR:", str.c_str(), 6)) {
		return style.fontColorError;
	}
	else if (0 == strncmp("OK:", str.c_str(), 3)) {
		return style.fontColorOK;
	}
	else {
		return style.fontColorWarning;
	}
}

Console::Console()
{
	this->size = cv::Size(0,0);
	img = Mat::zeros(size, CV_8UC3);
	rectangle(img, Point(0, 0), size, backGroundColor, -1);
}

Console::Console(cv::Size size)
{
	this->size = size;
	img = Mat::zeros(size, CV_8UC3);
	rectangle(img, Point(0, 0), size, backGroundColor, -1);
}

void Console::setSize(cv::Size size)
{
	this->size = size;
	img = Mat::zeros(size, CV_8UC3);
	rectangle(img, Point(0, 0), size, backGroundColor, -1);
}

void Console::addMessage(string message)
{
	if (messages.size() >= 10)
		messages.pop_front();
	messages.push_back(message);
}

cv::Mat Console::draw()
{
	if (messages.size() > 0) {
		//Draw background rectangle
		rectangle(img, Point(0, 0), size, backGroundColor, -1);
		
		//Get text Size
		int baseLine = 0;
		Size textSize = getTextSize(messages[0], style.fontFace, style.fontScale, 1, &baseLine);

		//Draw all messages from de deque, offset between strings = 5 pixels
		float y = 2; //Initial y offset
		deque<string>::iterator it;
		for (it = messages.begin(); it != messages.end(); it++)
		{
			Scalar fontColor = messageColor(*it);
			Point textOrg(2, (y + textSize.height));
			putText(img, (*it), textOrg, style.fontFace, style.fontScale, fontColor, 1, 8);
			y += (textSize.height) + 5;
		}
	}
	return img;
}
