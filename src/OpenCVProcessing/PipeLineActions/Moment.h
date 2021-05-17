/** @file		Moment.h
 *  @brief		Header file of the Moment child-class
 *  @details	Contains the definiton code Moment child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	pipeLineheader */
#pragma once

#include "PipeLineAction.h"

/** @class Moment
*	 @brief Child-classe, implements OpenCV's center of mass finding
*	 @ingroup pipeLine */
class Moment : public PipeLineAction {
private:
	cv::Moments m;		//!< struct containing spatial moment
	cv::Point center;	//!< vector containing all contour points
	int areaMax;		//!< highest value of the trackbar
	int area;			//!< current value of the trackbar, used as area filter

public:
	/** @brief Constructor
	*	@param name: (screen)name of mask action */
	Moment(const cv::String name);

	/** @brief sets the output of the action
	*	@details in this case: finding the center of mass at the first index of the vector. 
	*	If the input vector is empty the center is placed out of sight.
	*	@param data: pointer to the input data, should be a vector with points */
	void setAction(void* data);

	/** @brief gets the output of the action
	*	@return Point containing X and Y coordinats of the biggest contours center of mass */
	void* getAction();

	/** @brief gets the output of the action
	*	@return Point containing X and Y coordinats of the biggest contours center of mass */
	cv::Point* getCenterOfMass();

	/** @brief shows the action to the user
	*	@details uses cv::imshow(). The name of the window is the name of the pipeline action.
	*   Trackbar is added to set the size of the approximation accuracy */
	void showWindow();
};