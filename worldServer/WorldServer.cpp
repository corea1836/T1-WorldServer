#include <thread>
#include "WorldLoop.h"

int main()
{
    WorldLoop worldLoop;

    worldLoop.Start();

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    worldLoop.Stop();
    worldLoop.Join();
    return 0;
}
