cmake_minimum_required(VERSION 3.15)
project(livecast VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SWSCALE REQUIRED libswscale)
find_package(OpenCV REQUIRED)

include_directories(
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    include
    include/commons
)

add_executable(livecapture main.cpp
    src/capture.cpp
    src/encoder.cpp
    src/streamer.cpp
    src/jitter_buffer.cpp
    src/metrics.cpp
    src/commons/logger.cpp
)

target_link_libraries(livecapture
    ${AVFORMAT_LIBRARIES}
    ${AVCODEC_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWSCALE_LIBRARIES}
    ${OpenCV_LIBS}
    pthread
)
