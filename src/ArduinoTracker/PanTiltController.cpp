/** @file		PanTiltController.cpp
 *  @brief		C++ file of the PanTiltController class
 *  @details	Contains the implementation of the PanTiltController class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	Unocpp
 */
#pragma once
#include <HardwareSerial.h>
#include "PanTiltController.h"

PanTiltController* PanTiltController::instance = 0;

PanTiltController::PanTiltController(uint8_t panPin, uint8_t tiltPin) {
	this->panPin = panPin;
	this->tiltPin = tiltPin;
	this->initServos();
}

void PanTiltController::initServos() {
	panServo.attach(panPin);
	tiltServo.attach(tiltPin);
	home();
}

uint8_t PanTiltController::limit(uint8_t angle) {

	if (angle > 180) {
		Serial.println("ERROR: Angle can't be bigger than 180 degrees");
		return 180;
	}
	if (angle < 0) {
		Serial.println("ERROR: Angle can't be smaller than 0 degrees");
		return 0;
	}
		

	return angle;
}

PanTiltController* PanTiltController::initialize(uint8_t panPin, uint8_t tiltPin) {
	if (0 == instance) {
		instance = new PanTiltController(panPin, tiltPin);
	}
	else {
		Serial.println("ERROR: Pan tilt controller already initialized");
	}
	return instance;
}

void PanTiltController::setPosition(uint16_t pan, uint16_t tilt) {
	this->pan = limit(pan);
	this->tilt = limit(tilt);

	panServo.write(this->pan);
	tiltServo.write(this->tilt);
}

void PanTiltController::setPositionOffSet(uint16_t pan, uint16_t tilt)
{
	this->pan += pan;
	this->tilt += tilt;

	setPosition(this->pan, this->tilt);
}

void PanTiltController::home() {

	this->pan = 90;
	this->tilt = 90;

	setPosition(this->pan, this->tilt);
}
