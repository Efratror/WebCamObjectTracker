/** @file		Main.cpp
 *  @brief		OpenCV proccesing for object tracking with a webcam and arduino uno
 *  @details	Contains the implemantation code for object tracking using OpenCV
 *  @author		Max Avontuur
 *  @version	1.0
 *  @date		24-4-2021
 *  @ingroup main */

/** Graphic Control include files */
#include "GraphicControles\Gui.h"

/** Pipe Line include files */
#include "PipeLineActions\Blur.h"
#include "PipeLineActions\Capture.h"
#include "PipeLineActions\Contour.h"
#include "PipeLineActions\ConvertColorSpace.h"
#include "PipeLineActions\Mask.h"
#include "PipeLineActions\Moment.h"
#include "PipeLineActions\PipeLineAction.h"

/** Serial Communication include files */
#include "SerialCom.h"

using namespace std;

cv::Mat src;                        //!< Object holding an OpenCV matrix for the capture source  @ingroup main
vector<PipeLineAction*> actions;    //!< All OpenCV pipeline actions  @ingroup main
SerialCom* sc;                      //!< Object preforming the serial communication  @ingroup main
GUI* g;                             //!< Object holding the grafic user interface   @ingroup main
Capture webCam;                     //!< Object holding the capture device @ingroup main
char arduinoCommand[100];           //!< Command to be send to the arduino @ingroup main */


/** @brief Scale funtion
    @details Scales the input to a range. Range is defined by rMax and tMax.
    Where rMax is the maximum of the input range and tMax is the maximum of the target(output) range
    @note function assums that for both ranges the minimum is the negative maximum
    @param input: input to scale
    @param rMax: maximun of the input range
    @param tMax: maximum of the target(output) range
    @return int: scaled value from input to target range
    @ingroup main */
int scale(float input, float rMax, float tMax)
{
    float rMin = -rMax;
    float tMin = -tMax;
    return static_cast<int>(((input - rMin) / (rMax - rMin))*(tMax-tMin)+tMin);
}

/** @brief Main function
*    @details sets up a source Matrix, creates the OpenCV pipeline, starts serial Communication with an Arduino Unoand
*    initiates a graphic user interface.Continues until the escape - key is pressed or the console window is closed.
*    In each loop it captures an image of the webcam.Excecutes the pipeline actions.Sends the output of the pipeline to
*    the arduino and shows the appropriat windows on screen.
*
*    @note setup for the serial communication
*    - COM port : COM4
*    - Bauderate : 9600
*    - data size : 8 bits
*    - parity : none
*    - stop bits : 1
*
*    @return int exit-code */
int main()
{
    //Webcam object
    webCam = Capture(0, cv::CAP_ANY);

    //Create pipeline
    actions.push_back(new Blur("Blurred"));
    actions.push_back(new ConvertColorSpace("HSV"));

    #ifdef _DEBUG //Visual studio debug mode
        HSV_MASK_VALUES testMask{ 0,87,100,9,211,255 };
        actions.push_back(new Mask("Mask", testMask));
    #else //Release mode
        actions.push_back(new Mask("Mask"));
    #endif // DEBUG
    
    actions.push_back(new Contour("Contours"));
    actions.push_back(new Moment("Moment"));

    //Start serial communication
    sc = SerialCom::initialize("COM4",9600, 8, 'N', 1);
    sprintf_s(arduinoCommand, "Home\n");
    sc->write(arduinoCommand);

    //Create grafic user interface
    g = new GUI(actions);

    //Loop until Esc-key pressed
    while (cv::waitKey(33) != 27)
    {
        //Get input source
         webCam.getFeed(src);
         if (src.empty())
             src = cv::imread("oranje_pingpongbal.jpg", cv::IMREAD_COLOR);
             
        //Run pipeline, every input gets its output from the previous action
        vector<PipeLineAction*>::iterator it;
        actions[0]->setAction(&src);
        for (it = actions.begin()+1 ; it != actions.end(); it++)
        {
            (*it)->setAction((*(it - 1))->getAction());        
        }  

        //Get output of the pipeline
        cv::Point c;
        Moment* m = dynamic_cast<Moment*>(actions[actions.size() - 1]);
        m ? c = *m->getCenterOfMass() : c = cv::Point(-10, -10);
        
        if (c.x >= 0 && c.y >= 0) {
            //Translate center of mass to reasonable x and y coordinats
            float yInput = (src.rows / static_cast<float>(2)) - c.y;
            float xInput = c.x - (src.cols / static_cast<float>(2));

            //Scale to range of -15° to 15° this because other wise the arduino flips (movement is to slow)
            //X(pan) is inverted because of mirrored image
            int yOut = scale(yInput, src.rows / static_cast<float>(2), 15);
            int xOut = -scale(xInput, src.cols / static_cast<float>(2), 15);

            //Write to serial
            if (g->trackingActive()) {
                sprintf_s(arduinoCommand,"PTO%d:%d\n", xOut, yOut);
                sc->write(arduinoCommand);
            }
        }

        //Read serial input
        sc->readString();
        if (sc->newMessageAvailable())
            g->addMessage(sc->getLastMessage()->c_str());

        //Show images
        g->showOutput(src, &c);
        g->showWindows(actions);
       
    }
    cv::destroyAllWindows();
    return 0;
}