#include "NetworkService.h"

#include <boost/asio/post.hpp>

NetworkService::NetworkService(uint16_t port)
    : _ioContext()
    , _port(port)
    , _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port))
{
}

NetworkService::~NetworkService()
{
    Stop();
    Join();
}

void NetworkService::Start()
{
    _thread = std::thread([this]
    {
       Run();
    });
}

void NetworkService::Stop()
{
    boost::asio::post(_ioContext, [this]()
    {
       _acceptor.close();
    });
}

void NetworkService::Join()
{
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void NetworkService::Run()
{
    AsyncAccept();
    _ioContext.run();
}

void NetworkService::AsyncAccept()
{
    _acceptor.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket)
    {
       if (!error)
       {
           std::printf("Start Accept Client!\n");

           AsyncAccept();
       }
    });
}
