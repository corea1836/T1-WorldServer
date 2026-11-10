#include <iostream>
#include <thread>

int main()
{
    bool bIsEnd = false;
    bool* bp = &bIsEnd;
    std::thread t([bp]
    {
        int count = 0;
        while (true)
        {
            if (*bp == true)
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
    bIsEnd = true;

    t.join();

    return 0;
}
