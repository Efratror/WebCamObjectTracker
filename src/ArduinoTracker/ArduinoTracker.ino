/** @file		ArduinoTracker.ino
 *  @brief		Arduino project
 *  @details	Contains the implementation code for an arduino uno pan tilt module
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	mainUno
 */
#include "CommandParser.h"
#include "PanTiltController.h"
#include "Servo.h"

 /** @brief Pan and tilt controller object pointer
 	@ingroup mainUno
*/
PanTiltController* controller;

/** @brief Command parser object pointer
	@ingroup mainUno
*/
CommandParser* parser;

/** @brief Setup function
*	@details Opens the serial port. Initializes the PanTiltController, CommandParser and sends a "welkom"-message over the serialport.
*	@note
* - Bauderate:	  9600
* - Pan PWM-pin:  9
* - Tilt PWM-pin: 10
* 	@ingroup mainUno
*/
void setup() {
	Serial.begin(9600);
	while (!Serial);
	controller = PanTiltController::initialize(9, 10);
	parser = CommandParser::initialize();
	Serial.println();
	Serial.println("==== Pan & Tilt module for Arduino Uno V1.0 ====");
	Serial.println("Servo's initialized");
	Serial.println("Waiting for command");
}

/** @brief Continous loop function
*	@details Main program loop, continuously checks the serialport for commands and takes the appropriate action based on the command type
*	Actions are:
*	- Waiting, no command received
*	- PanTiltOffset, Offset current pan and tilt by x, y degrees
*	- PanTilt, Set pan tilt to x and y degrees
*	- Home, Home the pan tilt module
*	- Errors 
		- Command not recognized
*		- Unknown cause
* 	@ingroup mainUno
*/
void loop() {
	switch (parser->parse())
	{
	// No Command received
	case CommandParser::WAITING:
		break;
	// Pan Tilt offset command received
	case CommandParser::PAN_TILT_OFFSET: {
		int pan, tilt;
		sscanf(parser->getCommand(), "PTO%d:%d", &pan, &tilt);
		Serial.print("OK: ");
		Serial.print(pan);
		Serial.print(" Pan offset, ");
		Serial.print(tilt);
		Serial.println(" Tilt offset");
		controller->setPositionOffSet(pan, tilt);
		break;
	}
	// Pan Tilt command received
	case CommandParser::PAN_TILT: {
		int pan, tilt;
		sscanf(parser->getCommand(), "PT%d:%d", &pan, &tilt);
		Serial.print("OK: ");
		Serial.print(pan);
		Serial.print(" Pan, ");
		Serial.print(tilt);
		Serial.println(" Tilt");
		controller->setPosition(pan, tilt);
		break;
	}
	// Homing command received
	case CommandParser::HOME:
		controller->home();
		Serial.println("OK: Home");
		break;
	// Parser doens't recognize the command
	case CommandParser::ERROR:
		Serial.println("ERROR: Command not recognized");
		break;
	// Unkown error
	default:
		Serial.println("ERROR: cause unknown");
		break;
	}
}