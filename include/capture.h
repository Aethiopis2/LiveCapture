/**
 * @brief This file contains macros capturing and managing the WebCam stream.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */
#pragma once


//===================================================================|
// Includes
//===================================================================|
#include <opencv2/opencv.hpp>
#include <string>



//===================================================================|
// Class
//===================================================================|
/**
 * @class CaptureSession
 * @brief This class manages the session for capturing video from a webcam.
 */
class CaptureSession
{
public:

    CaptureSession(int deviceID = 0, int width = 640, int height = 480, int fps = 30);
    ~CaptureSession();

    void Init();
    void Start();
    cv::Mat GrabFrame();

private:

    int deviceID;           ///< ID of the webcam device
    int width;              ///< Width of the video frame
    int height;             ///< Height of the video frame
    int fps;                ///< Frames per second for the video capture
    cv::VideoCapture cap;   ///< OpenCV VideoCapture object for managing webcam input
    bool isInitialized;     ///< Flag to check if the session is initialized
};