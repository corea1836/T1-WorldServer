#include <thread>
#include <atomic>
#include <csignal>
#include "WorldLoop.h"

static std::atomic<bool> stopRequested = false;

static void OnSignal(int)
{
    stopRequested.store(true);
}

int main()
{
    std::signal(SIGINT, OnSignal);
    std::signal(SIGTERM, OnSignal);

    WorldLoop worldLoop;

    worldLoop.Start();

    while (stopRequested.load() == false)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    worldLoop.Stop();
    worldLoop.Join();
    return 0;
}
