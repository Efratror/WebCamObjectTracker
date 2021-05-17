/** @file		Mask.h
 *  @brief		Header file of the Mask child-class
 *  @details	Contains the definiton code Mask child-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLineheader */
#pragma once

#include "PipeLineAction.h"

/** @struct HSV_MASK_VALUES Mask.h 
*	@brief Struct to easily add predifined maks values
*	@ingroup pipeLine */
struct HSV_MASK_VALUES
{
	int lowH,	//!< low Hue value
	lowS,		//!< low Saturation value
	lowV,		//!< low Value value
	highH,		//!< high Hue value
	highS,		//!< high Saturation value
	highV;		//!< high Value value
};

 /** @class Mask
	 @brief Child-classe, applies a mask to the input matrix
	 @ingroup pipeLine */
class Mask : public PipeLineAction {
private:

	const int maxValueH = 180;		//!< maximum value of the hue trackbar
	const int maxValue = 255;		//!< maximum value of the saturation and value trackbars
	const int maxValuePixel = 10;	//!< maximum value of the associated trackbar

	int lowH; //!< current value of the low hue trackbar
	int lowS; //!< current value of the low saturation trackbar
	int lowV; //!< current value of the low value trackbar

	int highH; //!< current value of the high hue trackbar
	int highS; //!< current value of the high saturation trackbar
	int highV; //!< current value of the high value trackbar

	int pixelSize; //!< current value of the erode and dilate size, based on the pixelsize trackbar position

public:
	/** @brief Constructor
	*	@param name: (screen)name of mask action */
	Mask(const cv::String name);

	/** @brief Constructor
	*	@param name: (screen)name of mask action
	*	@param hsv: struct containing the HGV mask values */
	Mask(const cv::String name, HSV_MASK_VALUES hsv);

	/** @brief sets the output of the action
	*	@details in this case: applying a mask to the input matrix. The mask is based on the trackbar values.
	*	@param data: pointer to the input data, should be a OpenCV matrix */
	void setAction(void* data);

	/** @brief shows the action to the user
	*	@details uses cv::imshow(). The name of the window is the name of the pipeline action.
	*	Trackbars are added to set max and min values of
	*	- Hue
	*	- Saturation
	*	- Value */
	void showWindow();

private:
	/** @brief Handles the change trackbar event for the low hue trackbar
	*	@details sets the trackbar position bepending on the min of the high and low value
	*	@param data: pointer to the mask object associated with the trackbar */
	static void onLowHTreshTrackbar(int, void* data);

	/** @brief Handles the change trackbar event for the high hue trackbar
	*	@details sets the trackbar position bepending on the min of the high and low value
	*	@param data: pointer to the mask object associated with the trackbar */
	static void onHighHTreshTrackbar(int, void* data);

	/** @brief Handles the change trackbar event for the low saturation trackbar
	*	@details sets the trackbar position bepending on the min of the high and low value
	*	@param data: pointer to the mask object associated with the trackbar */
	static void onLowSTreshTrackbar(int, void* data);

	/** @brief Handles the change trackbar event for the high saturation trackbar
	*	@details sets the trackbar position bepending on the min of the high and low value
	*	@param data: pointer to the mask object associated with the trackbar */
	static void onHighSTreshTrackbar(int, void* data);

	/** @brief Handles the change trackbar event for the low value trackbar
	*	@details sets the trackbar position bepending on the min of the high and low value
	*	@param data: pointer to the mask object associated with the trackbar */
	static void onLowVTreshTrackbar(int, void* data);

	/** @brief Handles the change trackbar event for the high value trackbar
	*	@details sets the trackbar position bepending on the min of the high and low value
	*	@param data: pointer to the mask object associated with the trackbar */
	static void onHighVTreshTrackbar(int, void* data);
};