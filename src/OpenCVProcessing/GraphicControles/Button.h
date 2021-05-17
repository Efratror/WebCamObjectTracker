/** @file		Button.h
 *  @brief		header file of the Button class
 *  @details	Contains the definition code Button class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup graphicheader */
#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc.hpp>

/** @class Button
	 @brief A button that can be clicked. Member of @ref graphic Graphic group
	 @ingroup graphic */
class Button
{
private:
	cv::Point startPoint;	//!< X and Y coordinate of the topleft corner in pixels
	cv::Size size;			//!< Height and Width of the button in pixels
	cv::String text;		//!< Button Text
	bool clicked;			//!< Button state
	cv::Mat* img;			//!< Pointer to the img where the button should be drawn

	/** @brief Button style information */
	struct STYLE
	{
		int fontFace = cv::FONT_HERSHEY_SIMPLEX;				//!< Font type	
		float fontScale = 1;									//!< Font size
		cv::Scalar fontColor = cv::Scalar(205, 205, 205);		//!< Font color (white)
		cv::Scalar lineColor = cv::Scalar(113, 101, 99);		//!< Line color (black)
		cv::Scalar lineColorClicked = cv::Scalar(0, 255, 0);	//!< Line color when clicked (green)
		cv::Scalar fillColor = cv::Scalar(87, 73, 71);			//!< Fill color (grey)
		int lineThickness = 1;									//!< Line thickness in pixels
		int cornerRadius = 3;									//!< Radius of the corner in pixels
	}style; //!< button style information

	/** @brief creates a rectangle with rounded corners
	*	@details First draws the four edges, than draws the corners and last fills the rectangle.
	*	@param img: Pointer to the img where the rounded rectangle should be drawn
	*	@param topLeft: X and Y coordinate of the topleft corner in pixels
	* 	@param bottomRight: X and Y coordinate of the bottomright corner in pixels
	* 	@param lineColor: color of the button edge(line)
	* 	@param fillColor: color of the button
	* 	@param thickness: line thickness
	* 	@param cornerRadius: size of the rounded corner radius in pixels */
	void roundedRectangle(cv::Mat* img, cv::Point topLeft, cv::Point bottomRight, 
		const cv::Scalar lineColor, const cv::Scalar fillColor, const int thickness, const int cornerRadius);

public:
	/** @brief Default constructor */
	Button();

	/** @brief Constructor
	*	@param startPoint: X and Y coordinate of the topleft corner in pixels
	*	@param height: Height of the button in pixels
	*	@param text: Button text */
	Button(cv::Point startPoint, int height, cv::String text);

	/** @brief Draws the button to the image matrix
	*	@details the color of the line is based on the button state. The text is always centered in the middle of the button.
	*	@param img: Pointer to the image where the button should be drawn */
	void draw(cv::Mat* img);

	/** @brief Sets the topleft corner of the button
	*	@details is used to shift the startpoints of the buttons when creating the GUI.
	*	@param startPoint: X and Y coordinate of the topleft corner in pixels */
	void setStartPoint(cv::Point startPoint);

	/** @brief Checks if a mouse-click event happened inside the button
	*	@param x: X-part of the mouse event Coordinate
	*	@param y: Y-part of the mouse event Coordinate */
	void checkClick(int x, int y);

	/** @brief Gets the width of the button
	*	@return Width in pixels */
	int getWidth();

	/** @brief Gets the button state
	*	@return button state(Boolean) */
	bool getClick();
};
