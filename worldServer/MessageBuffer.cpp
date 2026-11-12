#include "MessageBuffer.h"

#include <cstring>


void MessageBuffer::WriteCompleted(std::size_t size)
{
    _writePos += size;
}

void MessageBuffer::ReadCompleted(std::size_t size)
{
    _readPos += size;
}

void MessageBuffer::Compact()
{
    std::size_t remainDataSize = GetDataSize();
    std::memmove(_buffer.data(), GetReadPointer(), remainDataSize);
    _readPos = 0;
    _writePos = remainDataSize;
}
