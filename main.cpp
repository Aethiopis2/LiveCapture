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
    cout << "[LiveCapture] starting Live stream engine...\n";

    try
    {   
        // Initialize the CaptureSession with default parameters
        CaptureSession capture;
        capture.Init(); 
        capture.Start(); 

        while (true)
        {
            auto frame = capture.GrabFrame(); // Grab a frame from the webcam
            if (!frame.empty())
            {
                 std::cout << "[Frame] Captured: " << frame.cols << "x" << frame.rows << "\n";

                 // do stuff here
            } // end if

            
        } // end while
    } // end try
    catch (const std::runtime_error& e)
    {
        cerr << "Error: " << e.what() << endl; 
        return EXIT_FAILURE; 
    } // end catch 

    return EXIT_SUCCESS; // Exit with success status
} // end main