/** @file		Capture.h
 *  @brief		Header file of the Capture class
 *  @details	Contains the definiton code Capture class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLineheader */

#pragma once
#include "PipeLineAction.h"
/** @class Capture
*	@brief Opens the webcam and captures its feed if available.
*	@ingroup pipeLine */
class Capture {
private:

	cv::VideoCapture cap;	//!< Object holding the capture device
	int deviceId;			//!< Device identification number
	int apiId;				//!< Device capture API identification number
	cv::Mat src;			//!< Object holding the capture image(source)
	bool deviceOpened;		//!< Device opened flag

public:
	/** @brief Default constructor */
	Capture();

	/** @brief Constructor
	*	@param deviceID: number of the device
	*	@param apiID: device capture API number */
	Capture(int deviceID, int apiID);

	/** @brief gets the webcam feed
	*	@param src: Pointer to a source OpenCV matrix
	*	@returns succes or error */
	int getFeed(cv::Mat& src);
};