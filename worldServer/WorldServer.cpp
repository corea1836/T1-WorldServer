#include <iostream>
#include <thread>
#include <atomic>

int main()
{
    std::atomic<bool> bIsEnd = false;
    std::thread t([&bIsEnd]
    {
        int count = 0;
        while (true)
        {
            if (bIsEnd == true)
            {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (count++ % 20 == 0)
            {
                std::cout << "1\n";
            }
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    bIsEnd.store(true);

    t.join();

    return 0;
}
