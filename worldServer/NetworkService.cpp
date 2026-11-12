#include "NetworkService.h"

#include <boost/asio/post.hpp>
#include <cstdio>
#include "WorldSocket.h"

NetworkService::NetworkService(uint16_t port)
    : _ioContext()
    , _port(port)
    , _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port))
    , _updateTimer(_ioContext)
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
       for (const auto& socket: _sockets)
       {
           socket->CloseSocket();
       }
        _updateTimer.cancel();
    });
}

void NetworkService::Join()
{
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void NetworkService::Update()
{
    size_t eraseCount = std::erase_if(_sockets, [](const std::shared_ptr<WorldSocket>& socket)
    {
       return !socket->IsOpen();
    });

    if (eraseCount > 0)
    {
        std::printf("Erase Sockets: %zu\n", eraseCount);
    }

    _updateTimer.expires_after(std::chrono::seconds(1));
    _updateTimer.async_wait([this](const boost::system::error_code& error)
    {
        if (error)
        {
            std::printf("Update timer stopped: %s\n", error.message().c_str());
            return;
        }
       Update();
    });
}

void NetworkService::Run()
{
    AsyncAccept();
    Update();
    _ioContext.run();
}

void NetworkService::AsyncAccept()
{
    _acceptor.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket)
    {
       if (!error)
       {
           std::printf("Start Accept Client!\n");
           std::shared_ptr<WorldSocket> clientSocket = std::make_shared<WorldSocket>(std::move(socket));
           _sockets.push_back(clientSocket);
           clientSocket->Start();
           AsyncAccept();
       }
    });
}
