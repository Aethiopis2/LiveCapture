/**
 * @brief This file contains streamer-related definitions and declarations.
 * 
 * @author Rediet Worku
 * @date July 22nd 2025, Tuesday
 * @version 1.0
 */
#pragma once


//===================================================================|
// Includes
//===================================================================|
#include <string>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <sys/socket.h>
#include <netinet/ip.h>





//===================================================================|
// Class
//========================================================s===========|
class RTPStreamer
{
public:

    RTPStreamer(const std::string& ip, const uint16_t port);
    ~RTPStreamer();

    void Send_Frame(const uint8_t* data, size_t size, uint32_t timestamp);

private:

    int fds;
    sockaddr_in addr;

    uint16_t sequence_number;  ///< Sequence number for RTP packets
    uint32_t ssrc = 0x12345678;             ///< Synchronization source identifier

    void Send_RTP_Packet(const uint8_t* payload, size_t size, uint32_t timestamp);
};