/** @file		Button.cpp
 *  @brief		C++ file of the Button class
 *  @details	Contains the implementation code Button class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup graphiccpp
 */
#include "Button.h"

using namespace cv;

Button::Button() {
	this->startPoint = Point(0, 0);
	this->size = Size(0, 0);
	this->text = "";
	this->clicked = false;
	this->img = new Mat(1, 1, CV_8UC3);
};

Button::Button(cv::Point startPoint, int height, cv::String text) {
	int baseline = 0;
	this->startPoint = startPoint;
	this->size = Size(getTextSize(text, style.fontFace, style.fontScale, 1, &baseline).width + 4, height);
	this->text = text;
	this->clicked = false;
};

void Button::roundedRectangle(Mat* img, Point topLeft, Point bottomRight, const Scalar lineColor, const Scalar fillColor, const int thickness, const int cornerRadius)
{
	/* corners:
		* p1 - p2
		* |     |
		* p4 - p3
		*/
	Point p1 = topLeft;
	Point p2 = Point(bottomRight.x, topLeft.y);
	Point p3 = bottomRight;
	Point p4 = Point(topLeft.x, bottomRight.y);

	// draw straight lines
	line(*img, Point(p1.x + cornerRadius, p1.y), Point(p2.x - cornerRadius, p2.y), lineColor, thickness);
	line(*img, Point(p2.x, p2.y + cornerRadius), Point(p3.x, p3.y - cornerRadius), lineColor, thickness);
	line(*img, Point(p4.x + cornerRadius, p4.y), Point(p3.x - cornerRadius, p3.y), lineColor, thickness);
	line(*img, Point(p1.x, p1.y + cornerRadius), Point(p4.x, p4.y - cornerRadius), lineColor, thickness);

	// draw arcs
	ellipse(*img, p1 + Point(cornerRadius, cornerRadius), Size(cornerRadius, cornerRadius), 180.0, 0, 90, lineColor, thickness);
	ellipse(*img, p2 + Point(-cornerRadius, cornerRadius), Size(cornerRadius, cornerRadius), 270.0, 0, 90, lineColor, thickness);
	ellipse(*img, p3 + Point(-cornerRadius, -cornerRadius), Size(cornerRadius, cornerRadius), 0.0, 0, 90, lineColor, thickness);
	ellipse(*img, p4 + Point(cornerRadius, -cornerRadius), Size(cornerRadius, cornerRadius), 90.0, 0, 90, lineColor, thickness);

	//Fill the rectangle
	Point fillFrom(topLeft.x + 10, topLeft.y + 10);
	floodFill(*img, fillFrom, fillColor);
}

void Button::draw(Mat* img) {
	int baseLine = 0;
	Scalar lColor;
	if (this->clicked)
		lColor = style.lineColorClicked;
	else
		lColor = style.lineColor;

	Size textSize = getTextSize(text, style.fontFace, style.fontScale, 1, &baseLine);
	roundedRectangle(img, startPoint, Point(startPoint.x + size.width, startPoint.y + size.height), lColor, style.fillColor, 1, 3);
	Point textOrg((startPoint.x + size.width / 2 - textSize.width / 2), (startPoint.y + size.height / 2 + textSize.height / 2));
	putText(*img, text, textOrg, style.fontFace, style.fontScale, style.fontColor, 1, 8);

}

void Button::setStartPoint(Point startPoint) {
	this->startPoint = startPoint;
}

void Button::checkClick(int x, int y) {
	//Check if x and y lie within the button
	if ((x >= startPoint.x) && (x <= startPoint.x + size.width) && (y >= startPoint.y) && (y <= startPoint.y + size.height)) {
		clicked = !clicked;
	}
}

int Button::getWidth() {
	return size.width;
}

bool Button::getClick() {
	return clicked;
}