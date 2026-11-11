#pragma once
#include <thread>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>


class NetworkService
{
public:
    explicit NetworkService(uint16_t port);
    ~NetworkService();

    void Start();
    void Stop();
    void Join();

private:
    void Run();
    void AsyncAccept();

    boost::asio::io_context _ioContext;
    std::thread _thread;
    uint16_t _port;
    boost::asio::ip::tcp::acceptor _acceptor;
};

