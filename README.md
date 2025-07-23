# LiveCapture

LiveCapture is a C++ application for real-time video capture, encoding, and streaming using FFmpeg and OpenCV. It captures frames from a camera, encodes them (default: H.264), and streams the encoded video over RTP.

## Features

- Real-time video capture from camera devices
- Hardware/software video encoding via FFmpeg (H.264 by default)
- RTP streaming to a specified IP and port
- Modular design with separate capture, encoding, and streaming components

## Requirements

- C++17 or later
- [FFmpeg libraries](https://ffmpeg.org/) (`libavcodec`, `libavformat`, `libavutil`, `libswscale`)
- [OpenCV](https://opencv.org/) (for frame capture and processing)
- CMake 3.15+

## Building

1. Install dependencies (FFmpeg, OpenCV).
2. Clone this repository.
3. Build using CMake:

```sh
mkdir build
cd build
cmake ..
make
```

The executable `livecapture` will be generated in the `build/` directory.

## Usage

Run the application:

```sh
./build/livecapture
```

By default, it streams H.264-encoded video over RTP to `127.0.0.1:5004`.

## Project Structure

- [`main.cpp`](main.cpp): Application entry point and main loop
- [`include/`](include/): Header files for capture, encoder, streamer, etc.
- [`src/`](src/): Implementation files
- [`CMakeLists.txt`](CMakeLists.txt): Build configuration

## Customization

- Change the target IP/port in [`main.cpp`](main.cpp) by modifying the `RTPStreamer` instantiation.
- Adjust encoding parameters in [`Encoder`](include/encoder.h) and [`src/encoder.cpp`](src/encoder.cpp).

## Author

Rediet Worku  
July 22nd, 2025

## License
