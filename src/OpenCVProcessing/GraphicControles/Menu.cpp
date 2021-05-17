/** @file		Menu.cpp
 *  @brief		C++ file of the Menu class
 *  @details	Contains the implementation code Menu class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup graphiccpp
 */

#include "Menu.h"

using namespace cv;

Menu::Menu() {};

Menu::Menu(cv::Size size)
{
	img = Mat::zeros(size, CV_8UC3);
	rectangle(img, Point(0, 0), size, Scalar(182, 182, 182), -1);

};

void Menu::addButton(Point startPoint, int height, String text) {
	buttons.push_back(Button(startPoint, height, text));
}

Mat Menu::draw() {

	vector<Button>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
	{
		it->draw(&img);
	}

	return img;
}

void Menu::checkClicks(int x, int y) {

	vector<Button>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
	{
		it->checkClick(x, y);
	}

}

vector<Button>* Menu::getButtons() {
	return &buttons;
}