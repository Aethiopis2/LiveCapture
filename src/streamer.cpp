/**
 * @brief This file defines the Streamer class, which is responsible for handling streaming operations.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */

//===================================================================|
// Includes
//===================================================================|
#include "streamer.h"
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>





//===================================================================|
// Class
//===================================================================|
/**
 * @brief Constructor for the RTPStreamer class.
 * 
 * Initializes the socket and sets up the address for sending RTP packets.
 * 
 * @param ip The IP address to send RTP packets to.
 * @param port The port number to send RTP packets to.
 * @throws std::runtime_error if socket creation or address setup fails.
 */
RTPStreamer::RTPStreamer(const std::string& ip, const uint16_t port)
{
    fds = socket(AF_INET, SOCK_DGRAM, 0);
    if (fds < 0)
    {
        throw std::runtime_error("Failed to create socket");   
    } // end if

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0)
    {
        close(fds);
        throw std::runtime_error("Invalid address or address not supported");
    } // end if
} // end RTPStreamer constructor


//===================================================================|
/**
 * @brief Destructor for the RTPStreamer class.
 * 
 * Closes the socket if it is open.
 */
RTPStreamer::~RTPStreamer()
{
    if (fds >= 0)
    {
        close(fds);
    } // end if
} // end RTPStreamer destructor 


//===================================================================|
/**
 * @brief Sends a frame of data as RTP packets.
 * 
 * This method splits the frame data into chunks and sends each chunk
 * as an RTP packet with the specified timestamp.
 * 
 * @param data Pointer to the frame data.
 * @param size Size of the frame data in bytes.
 * @param timestamp Timestamp for the RTP packets.
 */
void RTPStreamer::Send_Frame(const uint8_t* data, size_t size, uint32_t timestamp)
{
    if (size == 0 || data == nullptr)
    {     
        throw std::runtime_error("Invalid frame data");
    } // end if 

    const size_t max_payload_size = 1400; // Maximum payload size for RTP packets
    size_t offset = 0;
    while (offset < size)
    {
        size_t chunk_size = std::min(max_payload_size, size - offset);
        Send_RTP_Packet(data + offset, chunk_size, timestamp);
        offset += chunk_size;
    } // end while
} // end Send_Frame


//===================================================================|
/**
 * @brief Sends an RTP packet with the given payload and timestamp.
 * 
 * This method constructs an RTP packet with the specified payload,
 * sequence number, and timestamp, and sends it over the network.
 * 
 * @param payload Pointer to the payload data.
 * @param size Size of the payload in bytes.
 * @param timestamp Timestamp for the RTP packet.
 */
void RTPStreamer::Send_RTP_Packet(const uint8_t* payload, size_t size, uint32_t timestamp)
{
    uint8_t rtp_header[12] = {0};

    rtp_header[0] = 0x80; // Version 2, no padding, no extension
    rtp_header[1] = 96;   // Payload type (dynamic type for
    rtp_header[2] = (sequence_number >> 8) & 0xFF; // Sequence number high byte
    rtp_header[3] = sequence_number & 0xFF;        // Sequence
    rtp_header[4] = timestamp >> 24;
    rtp_header[5] = timestamp >> 16;
    rtp_header[6] = timestamp >> 8;
    rtp_header[7] = timestamp & 0xFF;
    rtp_header[8] = ssrc >> 24;
    rtp_header[9] = ssrc >> 16;
    rtp_header[10] = ssrc >> 8;
    rtp_header[11] = ssrc & 0xFF;

    std::vector<uint8_t> packet;
    packet.insert(packet.end(), rtp_header, rtp_header+12);
    packet.insert(packet.end(), payload, payload + size);

    sendto(fds, packet.data(), packet.size(), 0, (sockaddr*)&addr, sizeof(addr));
    sequence_number++; // Increment sequence number
} // end Send_RTP_Packet