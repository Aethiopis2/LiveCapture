/**
 * @brief This file contains encoder class definitions and related functions.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */

//===================================================================|
// Includes
//===================================================================|
#include "encoder.h"




//===================================================================|
// Class
//===================================================================|
/**
 * @brief constructor initializes the encoder
 */
Encoder::Encoder(int width, int height, int fps)
    : width(width), height(height), fps(fps), codec(nullptr), 
      ctx(nullptr), frame(nullptr), packet(nullptr), frameCount(0) { }


//===================================================================|
/**
 * @brief the destroyer
 */
Encoder::~Encoder()
{
    if (ctx) avcodec_free_context(&ctx);
    if (frame) av_frame_free(&frame);
    if (packet) av_packet_free(&packet);
} // end Destructor


//===================================================================|
/**
 * @brief Initializes the encoder with the specified codec.
 * 
 * @param codecId The codec ID to use for encoding (default is H.264).
 * @return true if initialization was successful, false otherwise.
 */
void Encoder::Init(AVCodecID codecId)
{
    // Initialize the codec
    codec = (AVCodec*)avcodec_find_encoder(codecId);
    if (!codec) 
    {
        throw std::runtime_error("Codec not found");
    }

    // Allocate the codec context
    ctx = avcodec_alloc_context3(codec);
    if (!ctx) {
        throw std::runtime_error("Could not allocate video codec context");
    }

    // Set codec parameters
    ctx->bit_rate = 4000000; // 4 Mbps
    ctx->width = width;
    ctx->height = height;
    ctx->time_base = {1, fps};
    ctx->framerate = {fps, 1};
    ctx->gop_size = 10; // Keyframe interval
    ctx->max_b_frames = 1;
    ctx->pix_fmt = AV_PIX_FMT_YUV420P;

    // Open the codec
    if (avcodec_open2(ctx, codec, nullptr) < 0) 
    {
        throw std::runtime_error("Could not open codec");
    }

    // Allocate frame and packet
    frame = av_frame_alloc();
    frame->format = ctx->pix_fmt;
    frame->width = ctx->width;
    frame->height = ctx->height;
    if (av_frame_get_buffer(frame, 32) < 0)
    {
        throw std::runtime_error("Could not allocate frame buffer");
    } // end if
    packet = av_packet_alloc();
} // end Init


//===================================================================|
/**
 * @brief Encodes a single frame and returns the encoded data.
 * 
 * @param input The input frame in BGR format.
 * @return A vector containing the encoded frame data.
 */
std::vector<uint8_t> Encoder::EncodeFrame(const cv::Mat& input)
{
    if (!ctx || !frame || !packet) 
    {
        throw std::runtime_error("Encoder not initialized");
    }

    std::vector<uint8_t> encoded_data;

    // Convert the input frame to YUV420P format
    Convert_To_YUV420P(input, frame);
    frame->pts = frameCount++; // Set presentation timestamp

    // Send the frame for encoding
    if (avcodec_send_frame(ctx, frame) < 0) 
    {
        throw std::runtime_error("Error sending frame for encoding");
    }

    // Receive the encoded packet
    int ret = avcodec_receive_packet(ctx, packet);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) 
    {
        // If no packet is available, return an empty vector
        return encoded_data;
    }
        // Other errors
    if (ret < 0)
    {
        throw std::runtime_error("Error receiving encoded packet");
    }

    // Store the encoded data in a vector
    encoded_data.insert(encoded_data.end(), packet->data, packet->data + packet->size);
    
    // Free the packet for reuse
    av_packet_unref(packet);
    
    return encoded_data;
} // end EncodeFrame


//===================================================================|
/**
 * @brief Converts the input BGR frame to YUV420P format.
 * 
 * @param bgr The input BGR frame.
 * @param yuv The output AVFrame in YUV420P format.
 */
void Encoder::Convert_To_YUV420P(const cv::Mat& bgr, AVFrame* yuv)
{
    cv::Mat resized;
    cv::resize(bgr, resized, cv::Size(width, height));

    cv::Mat yuvImg;
    cv::cvtColor(resized, yuvImg, cv::COLOR_BGR2YUV_I420);
    std::memcpy(yuv->data[0], yuvImg.data, width * height); // Y plane
    std::memcpy(yuv->data[1], yuvImg.data + width * height, width * height / 4); // U plane
    std::memcpy(yuv->data[2], yuvImg.data + width * height * 5 /4, width * height / 4); // V plane
} // end Convert_To_YUV420P