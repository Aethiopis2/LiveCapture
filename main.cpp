/**
 * @brief This function initializes the application and starts the main event loop.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */

//===================================================================|
// Includes
//===================================================================|
#include <iostream>
#include "capture.h"
#include "encoder.h"
#include "streamer.h"
#include <thread>

using namespace std;



//===================================================================|
/**
 * @brief Main function for the application.
 * 
 * Initializes the CaptureSession and starts capturing video frames.
 * 
 * @return int Exit status of the application.
 */
int main()
{
    CaptureSession camera;
    camera.Init();
    camera.Start();

    Encoder encoder;
    encoder.Init();

    RTPStreamer streamer("127.0.0.1", 5004);

    while (true) 
    {
        cv::Mat frame = camera.GrabFrame();
        if (frame.empty()) 
        {
            std::cerr << "Failed to grab frame" << std::endl;
            continue;
        } // end if

        std::vector<uint8_t> encodedData = encoder.EncodeFrame(frame);
        if (encodedData.empty()) 
        {
            std::cerr << "Failed to encode frame" << std::endl;
            continue;
        } // end if

        uint32_t timestamp = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
        streamer.Send_Frame(encodedData.data(), encodedData.size(), timestamp);

        std::this_thread::sleep_for(std::chrono::milliseconds(33)); // Simulate ~30 FPS
        cout << "sent stuff\n";
    } // end while
} // end main