/**
 * @brief This file contains encoder-related declarations and definitions.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */
#pragma once


//===================================================================|
// Includes
//===================================================================|
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
}

#include <opencv2/opencv.hpp>
#include <vector>



//===================================================================|
// Class
//===================================================================|
/**
 * @brief The Encoder class handles video encoding using FFmpeg.
 * 
 * It supports encoding frames in various formats, primarily YUV420P,
 * and provides methods to initialize the encoder and encode frames.
 */
class Encoder
{
public :

    Encoder(int width = 640, int height = 480, int fps = 30);
    ~Encoder();

    void Init(AVCodecID codecId = AV_CODEC_ID_H264);
    std::vector<uint8_t> EncodeFrame(const cv::Mat& frame);

private:

    int width;              ///< Width of the video frame
    int height;             ///< Height of the video frame
    int fps;                ///< Frames per second for the video encoding

    AVCodec* codec;         ///< Pointer to the AVCodec structure
    AVCodecContext* ctx;    ///< Pointer to the AVCodecContext structure
    AVFrame* frame;         ///< Pointer to the AVFrame structure for storing encoded frames
    AVPacket* packet;       ///< Pointer to the AVPacket structure for storing encoded packets
    int frameCount;         ///< Counter for the number of frames encoded
    
    void Convert_To_YUV420P(const cv::Mat& input, AVFrame* output);
};