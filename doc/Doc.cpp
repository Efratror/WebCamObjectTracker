/** \mainpage Web Cam tracker using OpenCV and an Arduino Uno

    @section intro Introductie:
    Dit project is de eind opdracht voor het vak: "Object Georienteerd programmeren".

    Het doel van de opdracht was om doormiddel van vision een object te volgen.
    Hierbij wordt gebruik gemaakt van OpenCV voor het vision gedeelte. Daarnaast wordt er een Arduino Uno gebruikt om het object daadwerkelijk fysiek te volgen.
    De student wilde graag meer experimenter met de aangeboden stof. Hierdoor is mogelijk de opbouw van de software een stuk complexer als misschien gewenst. 
    Echter heeft de student wel beter inzicht in essentiele C++ begrippen zoals: Pointers, klassen, overerving ect. \n \n

    Max Avontuur \n
    24-4-2021

    Deze opdracht bestaat dan ook uit twee delen: \n
    @ref OP \n
    @ref AR \n

    @note De documentatie is voornamelijk in het engels

    @subsection OP OpenCV processing
    Doormiddel van een webcam en openCV kan vrij eenvoudig de coordinaten verkregen worden van een object. Hiervoor moeten de volgende stappen worden doorlopen:
    - Verkrijgen van de webcam feed
    - Vervagen van het beeld
    - Omzetten kleur space
    - Toepassen masker
    - Vinden van de contouren
    - Middenpunt vinden van een contour

    Hierna kan het gevonden middenpunt geconverteerd en verzonden worden.

    Meer informatie vind u hier: @ref processing

    @subsection AR Arduino tracking
    De arduino software luistert naar de serial port en kijkt of er een herkenbaar commando langs komt. Op dat moment worden servo motoren aangestuurd. \n
    De volgende commando's worden herkend:
    - PTO'x':'y' (Pan & Tilt offset)
    - PT'x':'y'  (Pan & Tilt)
    - Home

    Meer informatie vind u hier: @ref tracking

*/

/** @defgroup WCT Webcam tracking software 
    @brief using Arduino Uno and OpenCV
*/

/** @defgroup tracking The Arduino Uno tracking module
    @brief This is the group contains arduino software
    @ingroup WCT
*/

/** @defgroup mainUno Main Function
    @brief The main entry point for the openCV processing console application
    @ingroup tracking
*/

/** @defgroup classes Classes
 *  @brief all classes used 
 *  @ingroup tracking
*/

/** @defgroup Unoheader Header Files
 *  @brief all header files
 *  @ingroup classes
*/

/** @defgroup Unocpp C++ Files
 *  @brief all C++ files
 *  @ingroup classes
*/

/** @defgroup processing The OpenCV proccesing module
    @brief This is the group containing als the image processing parts
    @ingroup WCT
*/

/** @defgroup main Main Function
@brief This group is the main entry point for the openCV processing console application
@ingroup processing
*/

/** @defgroup graphic GUI classes
 *  @brief all classes used for the graphic user interface
 *  @ingroup processing
*/

/** @defgroup graphicheader Header Files
 *  @brief all header files
 *  @ingroup graphic
*/

/** @defgroup graphiccpp C++ Files
 *  @brief all C++ files
 *  @ingroup graphic
*/

/** @defgroup pipeLine PipeLine classes
 *  @brief all classes used for the OpenCV pipeLine
 *  @ingroup processing
*/

/** @defgroup pipeLineheader Header Files
 *  @brief all header files
 *  @ingroup pipeLine
*/

/** @defgroup pipeLinecpp C++ Files
 *  @brief all C++ files
 *  @ingroup pipeLine
*/

/** @defgroup serial Serial Communication
 *  @brief Serial communication with an Arduino Uno
 *  @ingroup processing
*/

/** @fn main
    @brief Main function
*	@details sets up a source Matrix, creates the OpenCV pipeline, starts serial Communication with an Arduino Uno and 
    initiates a graphic user interface. Continues until the escape-key is pressed or the console window is closed. 
    In each loop it captures an image of the webcam. Excecutes the pipeline actions. Sends the output of the pipeline to
    the arduino and shows the appropriat windows on screen.

    @note setup for the serial communication
    - COM port: COM4
    - Bauderate: 9600
    - data size: 8 bits
    - parity: none
    - stop bits : 1

    @ingroup main
*/