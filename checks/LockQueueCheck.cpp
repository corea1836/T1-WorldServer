#include <iostream>
#include <thread>

#include "../worldServer/LockQueue.h"

struct Item
{
    int sequence;
    int id;
};

void Push(LockQueue<Item>& queue, int* seq, int id, std::atomic<int>& doneCount)
{
    for (int i = 0; i < 100000; i++)
    {
        queue.Push(Item((*seq)++, id));
    }

    doneCount.fetch_add(1);
}

int main()
{
    LockQueue<Item> queue;

    int t1Seq = 0;
    int t2Seq = 0;
    int t3Seq = 0;
    int t4Seq = 0;
    std::atomic<int> doneCount = 0;
    std::thread t1([&queue, p = &t1Seq, &doneCount] { Push(queue, p, 0, doneCount); });
    std::thread t2([&queue, p = &t2Seq, &doneCount] { Push(queue, p, 1, doneCount); });
    std::thread t3([&queue, p = &t3Seq, &doneCount] { Push(queue, p, 2, doneCount); });
    std::thread t4([&queue, p = &t4Seq, &doneCount] { Push(queue, p, 3, doneCount); });

    int count = 0;
    bool allDone = false;
    int result[4] = { -1, -1, -1, -1 };

    while (true)
    {
        bool done = doneCount == 4;

        std::optional<Item> item = queue.TryPop();
        if (!item.has_value())
        {
            if (done)
            {
                break;
            }
            continue;
        }

        Item inner = item.value();
        if (inner.sequence != result[inner.id] + 1)
        {
            break;
        }
        result[inner.id] = inner.sequence;
        count++;
    }
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    allDone = count == 400000;
    std::cout << "received: " << count << " allDone: " << allDone << '\n';
    return allDone ? 0 : 1;

}
