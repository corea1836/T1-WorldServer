#pragma once
#include <thread>
#include <vector>
#include <memory>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>


class WorldSocket;

class NetworkService
{
public:
    explicit NetworkService(uint16_t port);
    ~NetworkService();

    void Start();
    void Stop();
    void Join();

    void Update();

private:
    void Run();
    void AsyncAccept();

    boost::asio::io_context _ioContext;
    std::thread _thread;
    uint16_t _port;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::vector<std::shared_ptr<WorldSocket>> _sockets;
    boost::asio::steady_timer _updateTimer;
};

