#pragma once
#include <memory>
#include <array>
#include <cstdint>
#include <boost/asio/ip/tcp.hpp>

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
    std::array<uint8_t, 4096> _readBuffer;
};
