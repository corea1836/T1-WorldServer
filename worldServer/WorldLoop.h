#pragma once
#include <thread>
#include <atomic>

class WorldLoop
{
public:
    ~WorldLoop();

    void Start();
    void Stop();
    void Join();

private:
    void Run();

    std::thread _thread;
    std::atomic<bool> _bRunning = false;

};
