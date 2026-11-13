#pragma once

#include <deque>
#include <mutex>
#include <optional>
#include <utility>

template <typename T>
class LockQueue
{
public:
    void Push(T item)
    {
        {
            std::lock_guard<std::mutex> guard(_lock);
            _queue.push_back(std::move(item));
        }
    }

    std::optional<T> TryPop()
    {
        {
            std::lock_guard<std::mutex> guard(_lock);
            if (_queue.empty())
            {
                return std::nullopt;
            }

            T value = std::move(_queue.front());
            _queue.pop_front();
            return value;
        }
    }
private:
    std::mutex _lock;
    std::deque<T> _queue;
};

