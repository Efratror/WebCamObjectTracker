/** @file		GUI.h
 *  @brief		header file of the GUI class
 *  @details	Contains the definition code GUI class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup graphicheader */
#pragma once

#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include "Menu.h"
#include "Console.h"
#include "Button.h"
#include "../PipeLineActions/PipeLineAction.h"

using namespace std;

/**	@class GUI
*	@brief Contains the graphic user interface main class. Member of @ref graphic Graphic group
*	@ingroup graphic */
class GUI
{
private:
	const cv::String sourceWindow = "Tracking application"; //!< Name of the GUI window

	Menu menu;					//!< Object holding the menu class
	Console console;			//!< Object holding the console class
	vector<bool>buttonStates;	//!< All button states, from the menu in one vector
	bool tracking;				//!< Tracking active flag

	/** @brief Constructs the button state vector
	*	@details Loops over all buttons in the menu, adds the current state to the vector */
	void createButtonStates();

	/** @brief Checks the state of all menu buttons
	*	@details Loops over all buttons in the menu, sets its state in the vector */
	void checkButtonStates();

	/** @brief mouse call back function
	*	@details is called when a mouse event occurs, checks if it was a left-mousbutton press and 
	*	checks if the x,y coordinates are within a button.
	*	@param event: event type
	*	@param x: X-part of the mouse position
	*	@param y: Y-part of the mouse position
	*	@param userdata: pointer to the menu object. */
	static void onMouse(int event, int x, int y, int, void* userdata);

public:
	/** @brief Default constructor */
	GUI();

	/** @brief Constructor
	*	@details Creates a named window, a menu and a console. The menu buttons are named after the pipeline actions.
	*	Lines up the buttons length wise and creates a mouse event listener
	*	@param actions: vector containing pointers to all pipeline actions */
	GUI(vector<PipeLineAction*> actions);

	/** @brief shows the output Matrix to the user
	*	@details Including the tracking point
	*	@param src: source matrix where the trackingPoint is drawn to
	*	@param trackingPoint: center of the object to be tracked. */
	void showOutput(cv::Mat& src, cv::Point* trackingPoint);

	/** @brief shows pipeline action windows depending on the state of the corresponding menu button
	*	@details Loops over all actions and button states, showing or hiding the action windows.
	*	Also sets the tracking flag accourding to its button state
	*	@param actions: vector containing pointers to all pipeline actions */
	void showWindows(vector<PipeLineAction*> actions);

	/** @brief adds a message to the GUI console
	*	@param message: string containing the message */
	void addMessage(string message);

	/** @brief gets the tracking state
	*	@return bool: The state of the tracking start button. */
	bool trackingActive();
};
