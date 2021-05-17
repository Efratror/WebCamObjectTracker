/** @file		CommandParser.h
 *  @brief		Header file of the CommandParser class
 *  @details	Contains the definition of the CommandParser class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup	Unoheader */
#pragma once
#include <stdio.h>
#include <string.h>
#include <HardwareSerial.h>


/** @class CommandParser
*   @brief Parses the serial input for commands
*	@ingroup classes */
class CommandParser
{
private:
	char ch;			//!< Last read character from serial port
	char buf[255];		//!< All characters read from serial port
	uint8_t bufIndex;	//!< Location index off the last character placed in the buffer

	static CommandParser* instance; //!< pointer to current used instance

public:

	/** Parser commands */
	enum COMMANDS{
		WAITING,			//!< Indicates parser is waiting for a command ('/n' or '/r' character)
		PAN_TILT,			//!< Indicates a Pan and Tilt command
		PAN_TILT_OFFSET,	//!< Indicates a Pan and Tilt offset command
		HOME,				//!< Indicates a Home command
		ERROR				//!< Indicates that the command is not recognized
	};

private:
	/** @brief Constructor of the class*/
	CommandParser();

	/** @brief Checks the serial port for input 
	*	if the character is a line feed(LF) or carriage return(CR) the end of a command is signaled.
	*	@return int: 
	*	- -1: No serial.available 
	*	-  0: Command not ended
	*	-  1: Command ended */
	uint8_t createBuffer();
	
	/** @brief Checks the buffer for a command 
	*	Checks the buffer to see if there is a known command. If there isn't one, returns a command error
	*	@return uint8_t: index of a command or error @see COMMANDS */
	uint8_t checkCommand();

public:
	/** @brief Creates a new instance of the class if there isn't one 
	*	@note only one instance can excist because of the serial port
	*	@return: CommandParser: Pointer to object instance */
	static CommandParser* initialize();

	/** @brief Reads serial input and checks for commands 
	*	@see createBuffer()
	*	@see checkCommand()
	*	@return index of a command or error @see COMMANDS */
	uint8_t parse();

	/** @brief Get the command buffer 
	*	@return Pointer to the command buffer */
	char* getCommand();
};

