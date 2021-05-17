/** @file		PipeLineAction.h
 *  @brief		header file of the PipeLineAction base-class
 *  @details	Contains the definition code PipeLineAction base-class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	pipeLineheader */
#pragma once

 /** openCV include files */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

 /** c++ include files */
#include <vector>
#include<iostream>

/** @class PipeLineAction 
*	@brief Base-class for all OpenCV pipeline actions
*	@ingroup pipeLine */
class PipeLineAction
{
protected:
	cv::Mat img;		//!< Matrix which holds the image of the action
	bool show;			//!< Show action flag
	cv::String name;	//!< (screen)name of the pipeline action

public:
	/** @brief Default constructor */
	PipeLineAction();

	/** @brief Constructor 
	*	@param name: (screen)name of the pipeline action */
	PipeLineAction(const cv::String name);

	/** @brief sets the output of the action
	*	@details The parameter type is kept open, this provides the possibility to change the order of the pipeline
	*	and the type of parameter which is inserted. Special precautions have been taken to check if the parameter 
	*	type is suitable for the action.
	*	@param data: pointer to the input data */
	virtual void setAction(void* data) = 0;

	/** @brief gets the output of the action
	*	@details The return type is kept open, this provides the possibility to have 
	*   different outputs bassed on the implementation in the iherited class
	*	@return data: pointer to the image matrix */
	virtual void* getAction();

	/**@brief shows the action to the user
	*	@details uses cv::imshow(). The name of the window is the name of the pipeline action.
	*	it is possible to add trackbars to the implentations. */
	virtual void showWindow() = 0;

	/** @brief hides the action to the user
	*	@details destroys the OpenCV window based on the pipeline action name. */
	void hideWindow();

	/** @brief gets the pipeline action name
	*	@return name: (screen)name of the pipeline action. */
	cv::String getName();
};




