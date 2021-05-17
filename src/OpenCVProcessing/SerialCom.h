/** @file		SerialCom.h
 *  @brief		Header file of the SerialCom class
 *  @details	Contains the definiton code for the SerialCom class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *	@ingroup	serial */
#pragma once

 /** c++ include files */
#include <tchar.h>
#include <iostream>
#include <Windows.h>

/** custom include files */
#include "ceSerial.h"

using namespace std;
using namespace ce;

/** @class SerialCom
	@brief is responsable for the serial communication between PC-application and the Arduino Uno
	@ingroup	serial */
class SerialCom
{
private:
	ceSerial serial;				//!< Object which holds the ceSerial communication class
	string line;					//!< string of all characters in the serial message
	string lastMessage;				//!< last serial message
	bool newMessage;				//!< new message available flag
	static SerialCom* instance;		//!< pointer to the current used instance

	/** @brief Constructor
	*	@param portName: name of the COM-port
	*	@param baudeRate: baudeRate of the COM-port
	*	@param dataSize: size of the data
	*	@param parityType: paraity type
	*	@param nStopBits: number of stop bits */
	SerialCom(string portName, long baudeRate, int dataSize, char parityType, float nStopBits );

	/** @brief shows a error message on the console
	*	@details Also sets the message as lastMessage
	*	@param message: string containing the message */
	void publishError(string message);

	/** @brief shows a succes message on the console
	*	@details Also sets the message as lastMessage
	*	@param message: string containing the message */
	void publishSucces(string message);
	
public:
	/** @brief Creates a object if there isn't one already
		@note only one instance can excist because there can only be communicated with one Arduino Uno
	*	@param portName: name of the COM-port
	*	@param baudeRate: baude rate of the COM-port
	*	@param dataSize: size of the data
	*	@param parityType: parity type
	*	@param nStopBits: number of stop bits
	* @return: SerialCom: Pointer to object instance */
	static SerialCom* initialize(string portName, long baudeRate, int dataSize, char parityType, float nStopBits);

	/** @brief Sends a message(command) to the Arduino Uno
	*	@details Won't send a message if the COM-port isn't opened.
	*	@param message: command to be send */
	void write(char* message);

	/** @brief Reads the serial port for incomming messages.
	*	@details If ther isn't a character the readstring will break, so it's non-blocking. \n
	*	When the character is a line feed(LF) the serial message will be pushed on to the deque. */
	void readString();

	/** @brief Shows if a new message is recieved from the Serial input
	*	@return bool: new message available flag */
	bool newMessageAvailable();

	/** @brief Returns last message
		@return string: last serial message */
	string* getLastMessage();

};

