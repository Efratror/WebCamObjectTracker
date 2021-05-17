/**	@file		Menu.h
 *  @brief		header file of the Menu class
 *  @details	Contains the definition code Menu class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup graphicheader */
#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include "Button.h"

using namespace std;

/**	@class Menu
*	@brief Menu like structure with clickable buttons. Member of @ref graphic Graphic group
*	@ingroup graphic */
class Menu
{
private:
	cv::Mat img;			//!< Image matrix of the menu
	vector<Button>buttons;	//!< Vector holding all buttons

public:
	/** @brief Default constructor */
	Menu();

	/** @brief Constructor
	*	@param size: Height and width of the menu */
	Menu(cv::Size size);

	/** @brief Adds a button to the menu
	*	@details calls the Button constructor and pushes it to the button vector
	*	@param startPoint: X and Y coordinate of the topleft corner in pixels
	*	@param height: Height of the button in pixels
	*	@param text: Button text */
	void addButton(cv::Point startPoint, int height, cv::String text);

	/** @brief Draws all buttons to the image
	*	@details uses a iterating for loop.
	*	@return the image matrix */
	cv::Mat draw();

	/** @brief Checks if a mouse-click event happened inside on of the menubuttons
	*	@param x: X-part of the mouse event Coordinate
	*	@param y: Y-part of the mouse event Coordinate */
	void checkClicks(int x, int y);

	/** @brief Gets the buttons
	*	@return Pointer to the vector holding all menu buttons. */
	vector<Button>* getButtons();
};