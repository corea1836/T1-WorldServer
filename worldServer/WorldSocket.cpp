#include "WorldSocket.h"

#include <cstdio>

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
    _socket.async_read_some(boost::asio::buffer(_readBuffer),
    [self = shared_from_this()](const boost::system::error_code& error, size_t size)
    {
        if (error)
        {
            std::printf("Disconnected: %s\n", error.message().c_str());
            self->CloseSocket();
            return;
        }

        std::printf("Receive Byte: %zu\n", size);

        self->AsyncRead();
    });
}
