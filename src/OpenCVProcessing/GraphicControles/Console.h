/** @file		Console.h
 *  @brief		header file of the Console class
 *  @details	Contains the definition code Console class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup graphicheader */
#pragma once

#include <deque>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

/** @class Console
	@brief Displays the output of the serial communication. Member of @ref graphic Graphic group
	@ingroup graphic */
class Console {
private:

	const cv::Scalar backGroundColor = cv::Scalar(0, 0, 0); //!< Color of the console background
	cv::Mat img;			//!< Image matrix of the Console
	cv::Size size;			//!< Size of the image matrix
	deque<string> messages; //!< all messages from console

	/**@brief Console style information */
	struct STYLE
	{
		int fontFace = cv::FONT_HERSHEY_SIMPLEX;				//!< Font type
		float fontScale = .5;									//!< Font size
		cv::Scalar fontColorOK = cv::Scalar(0, 255, 0);			//!< Color of OK message (Green)
		cv::Scalar fontColorError = cv::Scalar(0, 0, 255);		//!< Color of ERROR message (Red)
		cv::Scalar fontColorWarning = cv::Scalar(0, 255, 255);	//!< Color of Warning/unknow message (Yellow)
	}style; //!< Console style information


	/** @brief returns color based on the message text
	*	@details 
	*		- "OK:" = green
	*		- "ERROR:" = red
	*		- unknow = yellow
	*	@param str: string containing the message
	*	@return Scalar: BGR color */
	cv::Scalar messageColor(std::string str);

public:
	/** @brief Default constructor */
	Console();

	/** @brief Constructor
	*	@details Creates a empty image, with hight and width set by size and fills it with a color.
	*	@warning, not working at the moment...
	*	@param size: Hight and width of the image matrix */
	Console(cv::Size size);

	/** @brief sets the size of the Matrix
	*	@details functionality is equal to Console(CV::Size size);
	*	@param size: Hight and width of the image matrix */
	void setSize(cv::Size size);

	/** @brief adds a message to de message deque
	*	@param message: string containing the message */
	void addMessage(string message);

	/** @brief Draws the serial communication messages to the image
	*	@details Loops over al messages and draws them with a height offset of 5 pixels between each message.
	*	@param serialCom: all serial communication messages
	*	@return the image matrix */
	cv::Mat draw();
};

