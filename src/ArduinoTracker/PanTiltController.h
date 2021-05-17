/** @file		PanTiltController.h
 *  @brief		Header file of the PanTiltController class
 *  @details	Contains the declaration of the PanTiltController class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	Unoheader */
#pragma once
#include "Servo.h"

/** @class PanTiltController
	@brief Controles the pan and tilt servo motors
	@ingroup classes */
class PanTiltController
{
private:
	Servo panServo;		//!< Servo motor object for pan
	Servo tiltServo;	//!< Servo motor object for tilt

	uint8_t panPin;		//!< pinnumber of the pan pwm
	uint8_t tiltPin;	//!< pinnumber of the tilt pwm

	uint16_t pan;		//!< Current pan angle [°]
	uint16_t tilt;		//!< Current tilt angle [°]

	static PanTiltController* instance; //!< Pointer to the current used instance

	/** @brief constructor of the class
	*	@param panPin: number of the pan pwm-pin
	*	@param tiltPin: number of the tilt pwm-pin */
	PanTiltController(uint8_t panPin, uint8_t tiltPin);

	/** @brief attaches the pin number to the servo's and homes the servo's */
	void initServos();

	/** @brief Limits an angle between 0° and 180°
	*	@details If nessecary sends an error over the serial port, indicating the input angle is out of range.
	*	When the angle is out of range it is clamped to 0° or 180°. Depending on at wich end the angle is out of range.
	*	@param angle: angle that needs to be checked
	*	@return limit: angle between 0° and 180° */
	uint8_t limit(uint8_t angle);

public:
	/** @brief Creates a object if there isn't one already
	*	@note only one instance can excist because there are only two motors available at the moment
	*	@param panPin: number of the pan pwm-pin
	*	@param tiltPin: number of the tilt pwm-pin 
	*	@return: PanTiltController: Pointer to object instance*/
	static PanTiltController* initialize(uint8_t panPin, uint8_t tiltPin);

	/** @brief Sets the position of the pan and tilt motor
	*   @details if nessecary limits both angles @see limit()
	*	@param pan: angle to set the pan motor to
	*	@param tilt: angle to set the tilt motor to */
	void setPosition(uint16_t pan, uint16_t tilt);

	/** @brief Sets the position of the pan and tilt motor
	*	@details if nessecary limits both angles @see limit()
	*	@param pan: angle to set the pan motor to
	*	@param tilt: angle to set the tilt motor to */
	void setPositionOffSet(uint16_t pan, uint16_t tilt);

	/** @brief Homes the pan and tilt motors
	*	@details Homing is done by setting both motors to 90 degrees */
	void home();
};

