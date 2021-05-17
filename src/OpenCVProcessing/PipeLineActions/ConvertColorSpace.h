/** @file		ConvertColorSpace.h
 *  @brief		Header file of the ConvertColorSpace child-class
 *  @details	Contains the definiton code ConvertColorSpace child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLineheader */

#pragma once
#include "PipeLineAction.h"
/** @class ConvertColorSpace
*	 @brief Child-classe, converts from BGR to HSV color space
*	 @ingroup pipeLine */
class ConvertColorSpace : public PipeLineAction {
public:
	/** @brief Constructor
	*	@param name: (screen)name of ConvertColorSpace action */
	ConvertColorSpace(const cv::String name);

	/** @brief sets the output of the action
	*	@details in this case: converting from BGR to HSV colorspace.
	*	@param data: pointer to the input data, should be a OpenCV matrix */
	void setAction(void* data);

	/** @brief shows the action to the user
	*	@details uses cv::imshow(). The name of the window is the name of the pipeline action. */
	void showWindow();

};