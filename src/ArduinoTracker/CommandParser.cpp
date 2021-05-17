/** @file		CommandParser.cpp
 *  @brief		C++ file of the CommandParser class
 *  @details	Contains the implementation of the CommandParser class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	Unocpp
 */
#include "CommandParser.h"

CommandParser* CommandParser::instance = 0;

CommandParser::CommandParser() {
	ch = '\0';
	bufIndex = 0;
}

uint8_t CommandParser::createBuffer() {
	if (Serial.available() > 0) {
		ch = Serial.read();
		if (ch != '\n' && ch != '\r') {
			buf[bufIndex] = ch;
			bufIndex++;
			return 0; // Add to buffer
		}
		else {
			//string termination
			buf[bufIndex] = '\0';
			bufIndex = 0;
			return  1; // Buffer full
		}
	}
	return -1;
}

uint8_t CommandParser::checkCommand() {
	
	if (0 == strncmp("PTO", buf, 3)) {
		return COMMANDS::PAN_TILT_OFFSET;
	}

	if (0 == strncmp(buf, "PT", 2)) {
		return COMMANDS::PAN_TILT;
	}

	if (0 == strncmp("Ho", buf, 2)) {
		return COMMANDS::HOME;
	}

	return COMMANDS::ERROR;
}

CommandParser* CommandParser::initialize() {
	if (0 == instance) {
		instance = new CommandParser;
	}
	else {
		Serial.println("ERROR: CommandParser is already initialized");
	}

	return instance;
}

uint8_t CommandParser::parse() {
	if (1 == createBuffer()) {
		return checkCommand();
	}

	return 0;
}

char* CommandParser::getCommand() {
	return buf;
}
