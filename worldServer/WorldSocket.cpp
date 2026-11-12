#include "WorldSocket.h"

#include <cstdio>
#include <cstring>
#include <cstdint>

struct PacketHeader
{
    std::uint16_t size = 0;
    std::uint16_t id = 0;
};

static_assert(sizeof(PacketHeader) == 4);

WorldSocket::WorldSocket(boost::asio::ip::tcp::socket &&socket)
    : _socket(std::move(socket))
{
}

void WorldSocket::Start()
{
    AsyncRead();
}

void WorldSocket::CloseSocket()
{
    _socket.close();
}

void WorldSocket::AsyncRead()
{
    _socket.async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetFreeSize()),
    [self = shared_from_this()](const boost::system::error_code& error, size_t bytesTransferred)
    {
        if (error)
        {
            std::printf("Disconnected: %s\n", error.message().c_str());
            self->CloseSocket();
            return;
        }

        std::printf("Receive Byte: %zu\n", bytesTransferred);
        self->_readBuffer.WriteCompleted(bytesTransferred);

        while (true)
        {
            if (self->_readBuffer.GetDataSize() < sizeof(PacketHeader))
            {
                break;
            }
            PacketHeader header;
            std::memcpy(&header, self->_readBuffer.GetReadPointer(), sizeof(PacketHeader));

            if (header.size < 4 || header.size > 4096)
            {
                self->CloseSocket();
                return;
            }

            if (header.size > self->_readBuffer.GetDataSize())
            {
                break;
            }

            std::printf("Receive Packet. Size: %hu\n", header.size);
            self->_readBuffer.ReadCompleted(header.size);
        }

        self->_readBuffer.Compact();

        self->AsyncRead();
    });
}
