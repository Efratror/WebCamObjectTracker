/** @file		Capture.cpp
 *  @brief		C++ file of the Capture class
 *  @details	Contains the implementation code Capture class
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 * 	@ingroup	pipeLinecpp
 */
#include "Capture.h"

using namespace std;
using namespace cv;

Capture::Capture()
{
	deviceId = 0;
	apiId = 0;
	deviceOpened = false;
}

Capture::Capture(int deviceID, int apiId) {
	this->deviceId = deviceID;
	this->apiId = apiId;

	cap.open(this->deviceId + this->apiId);
	deviceOpened = false;

	if (!cap.isOpened()) {
		std::cerr << "ERROR: Can't open camera feed" << std::endl;
	}
	else {
		std::cout << "Camera feed opened" << std::endl;
		deviceOpened = true;
	}
}

int Capture::getFeed(Mat& src) {
	if (deviceOpened) {
		cap.read(this->src);

		if (this->src.empty()) {
			std::cerr << "ERROR: Frame is blank" << std::endl;
			return -1;
		}
		else {
			src = this->src;
			return 1;
		}
	}
	else {
		std::cerr << "ERROR: No device opened" << std::endl;
		return -2;
	}
}