#include "WorldLoop.h"

#include <iostream>

void WorldLoop::Start()
{
    _bRunning.store(true);

    _thread = std::thread([this]
    {
        Run();
    });
}

void WorldLoop::Stop()
{
    _bRunning.store(false);
}

void WorldLoop::Join()
{
    _thread.join();
}

void WorldLoop::Run()
{
    int count = 0;
    while (true)
    {
        if (_bRunning == false)
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (count++ % 20 == 0)
        {
            std::cout << "1\n";
        }
    }
}
