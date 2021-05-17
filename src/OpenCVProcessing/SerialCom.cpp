/** @file		SerialCom.cpp
 *  @brief		C++ file of the SerialCom class
 *  @details	Contains the definiton code for the following classes
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup	serial
 */
#include "SerialCom.h"


SerialCom* SerialCom::instance = 0;

SerialCom::SerialCom(string portName, long baudeRate, int dataSize, char parityType, float nStopBits){
	string port = "\\\\.\\"+portName;
	serial = ceSerial(port, baudeRate, dataSize, parityType, nStopBits);

	int opend = serial.Open();
	switch (opend)
	{
	case 1:	 publishError("ERROR: No COM-port found named " + portName);	break;
	case 2:	 publishError("ERROR: Unable to clear serial buffer");			break;
	case 3:  publishError("ERROR: Unable to open COM-port");				break;
	case 4:  publishError("ERROR: Unable to set COM-port settings");		break;
	case 5:  publishError("ERROR: Unable to open COM-port");				break;
	case 6:  publishError("ERROR: Error creating read overlapped event");	break;
	case 7:  publishError("ERROR: Error creating write overlapped event");	break;
	case 8:  publishError("ERROR: Error getting time-outs");				break;
	case 9:  publishError("ERROR: Error setting time-outs");				break;
	case 0:  publishSucces("OK: Opend " + portName);						break;
	default: publishError("ERROR: An unspecified error occured");			break;
	}

	if (opend != 0)
		serial.Close();
}

void SerialCom::publishError(string message)
{
	lastMessage = message;
	std::cerr << lastMessage << std::endl;
	newMessage = true;
}

void SerialCom::publishSucces(string message)
{
	lastMessage = message;
	std::cout << lastMessage << std::endl;
	newMessage = true;
}

SerialCom* SerialCom::initialize(string portName, long baudeRate, int dataSize, char parityType, float nStopBits)
{
	if (instance == 0) {
		instance = new SerialCom(portName, baudeRate, dataSize, parityType, nStopBits);
	}

	return instance;
}

void SerialCom::write(char* message)
{
	if (serial.IsOpened()) {
		if (!serial.Write(message))
			publishError("ERROR: A write error occured");
	}
}

void SerialCom::readString() {

	bool succes = false;
	char ch = 0;
	do
	{
		ch = serial.ReadChar(succes);
		if (succes) {
			if ((ch >= 0) && (ch != 10) && (ch != 13))
				line += ch;
			if (ch == '\n') {
				lastMessage = line;
				newMessage = true;
				line = "";
			}
		}
	} while ((ch != '\n') && (succes==true));
	
}

bool SerialCom::newMessageAvailable()
{
	if (newMessage) {
		newMessage = false;
		return true;
	}
	return false;
}

std::string* SerialCom::getLastMessage()
{
	return &lastMessage;
}
