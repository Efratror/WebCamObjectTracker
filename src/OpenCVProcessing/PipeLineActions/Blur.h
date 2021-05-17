/** @file		Blur.h
 *  @brief		Header file of the Blur child-class
 *  @details	Contains the definiton code Blur child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLineheader */

#pragma once
#include "PipeLineAction.h"
/** @class Blur
*	@brief Child-classe, implements OpenCV's GaussianBlur
*	@ingroup pipeLine */
class Blur : public PipeLineAction {

private:
	const int maxValue = 20;	//!< maximum value of the associated trackbar
	int slider;					//!< current value of the associated trackba
	float sigma;				//!< Gaussian kernel standard deviation in X and Y direction
	int kernelSize;				//!< Gaussian kernel size in X and Y direction


public:
	/** @brief Constructor
	*	@param name: (screen)name of blur action */
	Blur(const cv::String name);

	/** @brief sets the output of the action
	*	@details in this case: bluring the input. The blursize is based on the trackbar value.
	*	@param data: pointer to the input data, should be a OpenCV matrix */
	void setAction(void* data);

	/** @brief shows the action to the user
	*	@details uses cv::imshow(). The name of the window is the name of the pipeline action.
	*	Trackbar is added to set the size of the Gaussion blur */
	void showWindow();

	/** @brief Handles the change trackbar event
	*	@details updates the kernelSize based on the trackbar position
	*	@param data: pointer to the blur object associated with the trackbar */
	static void onChange(int, void* data);
};

