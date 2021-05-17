/** @file		Contour.h
 *  @brief		Header file of the Contour child-class
 *  @details	Contains the definiton code Contour child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLineheader */

#pragma once
#include "PipeLineAction.h"
 /** @class Contour
	 @brief Child-classe, implements OpenCV's contour finding.
	 @details With area filtering and size sorting
	 @ingroup pipeLine */
class Contour : public PipeLineAction {
private:

	std::vector<std::vector<cv::Point>> contours;	//!< vector containing all contour points
	std::vector<std::vector<cv::Point>> polylines;	//!< vector containing all polyline points

	const cv::Scalar green{ 0,255,0 };				//!< color green
	const cv::Scalar red{ 0,0,255 };				//!< color red

	const int accuracyMax = 20;						//!< maximum value of the accuracy trackbar
	const int areaMax = 50;							//!< maximum value of the area trackbar

	int accuracy;									//!< current value of the accuracy trackbar
	int area;										//!< area value of the accuracy trackbar

public:
	/** @brief Constructor
	*	@param name: (screen)name of mask action */
	Contour(const cv::String name);

	/** @brief sets the output of the action
	*	@details Sets the action, in this case: finding all contours of the input matrix.
	*	And appying a area filter, bigger than the trackbar value multiplied by 10 contour color is green. 
	*	Smaller countours are painted red. If there are no contours big enough, the vector is cleared.
	*	@param data: pointer to the input data, should be a OpenCV matrix */
	void setAction(void* data);

	/** @brief gets the output of the action
	*	@return data: pointer to a vector with in a vector containing the points of all contours found */
	void* getAction();

	/** @brief shows the action to the user
	*	@details uses cv::imshow(). The name of the window is the name of the pipeline action.
	*   Trackbar is added to set the size of the approximation accuracy */
	void showWindow();
};
