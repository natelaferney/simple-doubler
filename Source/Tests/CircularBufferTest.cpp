#include "../CircularBuffer.h"
#include <vector>
#include <iostream>
    
int main() 
{
    CircularBuffer buffer = CircularBuffer(100);
    buffer.reset();
    buffer.setSampleRate(100);
    buffer.setReadPositionFromMilliseconds(500);
    std::cout << "Sample Rate: " << buffer.getSampleRate() << '\n';
    std::cout << "Buffer Size: " << buffer.getBufferSize() << '\n';
    std::cout << "Read Position: " << buffer.getReadPosition() << '\n';
    
    int dog;
    
    for (int i = 0; i < 1050; ++i)
    {
        //std::cout << buffer.getReadPosition() << '\n';
        buffer.write(i);
        dog = (int)buffer.read();
    }
    std::cout << "Last Read Position: " << buffer.getReadPosition() << "\n";
    std::cout << "Last Read Value: " << dog << "\n";
    return 0;
}