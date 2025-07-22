/**
 * @brief Definitions for capturing and managing the WebCam stream.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */

//===================================================================|
// Includes
//===================================================================|
#include "capture.h"




//===================================================================|
// Class
//===================================================================|
/**
 * @brief Constructor for CaptureSession.
 * 
 * Initializes the CaptureSession with default or specified parameters.
 * 
 * @param deviceID ID of the webcam device (default is 0).
 * @param width Width of the video frame (default is 640).
 * @param height Height of the video frame (default is 480).
 * @param fps Frames per second for the video capture (default is 30).
 */
CaptureSession::CaptureSession(int deviceID, int width, int height, int fps)
    : deviceID(deviceID), width(width), height(height), fps(fps), isInitialized(false)
{
} // end constructor


//===================================================================|
/**
 * @brief Destructor for CaptureSession.
 * 
 * Releases the VideoCapture object if it was opened.
 */
CaptureSession::~CaptureSession()
{
    if (cap.isOpened()) 
    {
        cap.release(); 
    } // end if
} // end destructor


//===================================================================|
/**
 * @brief Initializes the CaptureSession.
 * 
 * Opens the VideoCapture object with the specified device ID and sets the frame properties.
 * 
 * @throws std::runtime_error if the VideoCapture object cannot be opened.
 */
void CaptureSession::Init()
{
    // Initialize the VideoCapture object with the specified device ID
    std::string deviceIDStr = "/dev/video" + std::to_string(deviceID);
    cap.open(deviceIDStr);
    
    // Check if the VideoCapture object was successfully opened
    if (!cap.isOpened()) 
    {
        throw std::runtime_error("Could not open video device");
    } // end if

    // Set the frame width, height, and FPS
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FPS, fps);

    isInitialized = true;
} // end Init


//===================================================================|
/**
 * @brief Grabs a frame from the webcam.
 * 
 * Captures a single frame from the webcam and returns it as a cv::Mat object.
 * 
 * @return cv::Mat The captured frame.
 * @throws std::runtime_error if the session is not initialized or if the frame cannot be grabbed.
 */
void CaptureSession::Start()
{
    // Ensure the session is initialized before starting
    if (!isInitialized) 
    {
        throw std::runtime_error("CaptureSession not initialized");
    } // end if

    // Start capturing frames (this method can be extended to include more functionality)
} // end Start


//===================================================================|
/**
 * @brief Grabs a frame from the webcam.
 * 
 * Captures a single frame from the webcam and returns it as a cv::Mat object.
 * 
 * @return cv::Mat The captured frame.
 * @throws std::runtime_error if the session is not initialized or if the frame cannot be grabbed.
 */
cv::Mat CaptureSession::GrabFrame()
{
    // Ensure the session is initialized before grabbing a frame
    if (!isInitialized) 
    {
        throw std::runtime_error("CaptureSession not initialized");
    } // end if     

    cv::Mat frame;
    cap >> frame;
    return frame;
} // end GrabFrame