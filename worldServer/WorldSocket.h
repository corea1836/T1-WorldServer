#pragma once

#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include "MessageBuffer.h"

class WorldSocket: public std::enable_shared_from_this<WorldSocket>
{
public:
    explicit WorldSocket(boost::asio::ip::tcp::socket&& socket);
    void Start();
    void CloseSocket();

    bool IsOpen() const { return _socket.is_open(); }

private:
    void AsyncRead();
    boost::asio::ip::tcp::socket _socket;
    MessageBuffer _readBuffer;
};
