/** @file		GUI.cpp
 *  @brief		C++ file of the GUI class
 *  @details	Contains the implementation code GUI class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup graphiccpp
 */
#include "GUI.h"

using namespace cv;

void GUI::createButtonStates()
{
	vector<Button>::iterator it;
	vector<Button>* buttons = menu.getButtons();
	for (it = buttons->begin(); it != buttons->end(); it++)
	{
		buttonStates.push_back(it->getClick());
	}
}

void GUI::checkButtonStates()
{
	vector<Button>::iterator it;
	vector<bool>::iterator ws;
	vector<Button>* buttons = menu.getButtons();
	ws = buttonStates.begin();
	for (it = buttons->begin(); it != buttons->end(); it++)
	{
		*ws = it->getClick();
		ws++;
	}
}

void GUI::onMouse(int event, int x, int y, int, void* userdata)
{
	if (event != cv::EVENT_LBUTTONDOWN)
		return;
	static_cast<Menu*>(userdata)->checkClicks(x, y);
}

GUI::GUI() { tracking = false; };

GUI::GUI(vector<PipeLineAction*> actions)
{
	cv::namedWindow(sourceWindow, cv::WINDOW_AUTOSIZE);

	menu = Menu(Size(800, 40));
	console.setSize(Size(800, 180));

	//Create buttons
	cv::Point startPoint(5, 5);
	vector<PipeLineAction*>::iterator it;
	for (it = actions.begin(); it != actions.end(); it++)
	{
		menu.addButton(startPoint, 30, (*it)->getName());
	}

	menu.addButton(startPoint, 30, "Start Tracking");

	//shift start points of buttons to end of prev button
	vector<Button>* buttons = menu.getButtons();
	vector<Button>::iterator bt;
	for (bt = buttons->begin(); bt != buttons->end(); bt++)
	{
		bt->setStartPoint(startPoint);
		startPoint.x += bt->getWidth() + 5;
	}


	cv::setMouseCallback(sourceWindow, onMouse, &menu);
	createButtonStates();
}

void GUI::showOutput(Mat& src, Point* trackingPoint)
{
	Mat out;
	circle(src, *trackingPoint, 5, { 0,0,255 }, -1);

	out.push_back(menu.draw());
	resize(src, src, Size(800, 460));
	out.push_back(src);
	out.push_back(console.draw());

	imshow(sourceWindow, out);
}

void GUI::showWindows(vector<PipeLineAction*> actions)
{
	//get current button states
	checkButtonStates();

	//Show or hide windows depending on the buttons state
	vector<PipeLineAction*>::iterator ac;
	vector<bool>::iterator ws;
	ws = buttonStates.begin();
	for (ac = actions.begin(); ac != actions.end(); ac++)
	{
		*ws ? (*ac)->showWindow() : (*ac)->hideWindow();
		ws++;
	}

	*ws ? tracking = true : tracking = false;

}

void GUI::addMessage(string message)
{
	console.addMessage(message);
}

bool GUI::trackingActive()
{
	return tracking;
}
