#pragma once
#include <array>
#include <cstddef>

class MessageBuffer
{
public:
    std::byte* GetWritePointer() { return _buffer.data() + _writePos; }
    std::size_t GetFreeSize() const { return _buffer.size() - _writePos; }
    void WriteCompleted(std::size_t size);
    std::byte* GetReadPointer() { return _buffer.data() + _readPos; }
    std::size_t GetDataSize() const { return _writePos - _readPos; }
    void ReadCompleted(std::size_t size);
    void Compact();
private:
    std::size_t _readPos = 0;
    std::size_t _writePos = 0;
    std::array<std::byte, 4096> _buffer = {};

};
