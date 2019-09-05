#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int sizeOfBuffer)
{
	buffer.resize(sizeOfBuffer, 0.0f);
	bufferSize = sizeOfBuffer;
	writePosition = 0;
	readPosition = bufferSize - 1;
}

CircularBuffer::~CircularBuffer()
{
}

void CircularBuffer::resize(int newSize)
{
	buffer.resize(newSize, 0.0f);
	bufferSize = newSize;
}

void CircularBuffer::setSampleRate(int newSampleRate)
{
	sampleRate = newSampleRate;
}

void CircularBuffer::setReadPositionFromMilliseconds(int milliseconds)
{
	int offset = (int)(((milliseconds / 1000.0f) * sampleRate) + .5);
	//readPosition = std::abs(writePosition - offset) % bufferSize;
	int temp = writePosition - offset;
    while(temp < 0) temp += bufferSize;
	//readPosition = (temp < 0) ? temp + bufferSize : temp;
    readPosition = temp % bufferSize;
}

float CircularBuffer::read()
{
	float ret = buffer[readPosition];
    readPosition += 1;
	readPosition = (readPosition >= bufferSize) ? 0 : readPosition;
	return ret;
}

void CircularBuffer::write(float val)
{
	buffer[writePosition++] = val;
	writePosition = (writePosition >= bufferSize) ? 0 : writePosition;
}

void CircularBuffer::reset()
{
	std::fill(buffer.begin(), buffer.end(), 0.0f);
	writePosition = 0;
	readPosition = bufferSize - 1;
}

const int CircularBuffer::getSampleRate()
{
	return sampleRate;
}

const int CircularBuffer::getBufferSize()
{
	return bufferSize;
}

int CircularBuffer::getReadPosition()
{
    return readPosition;
}

int CircularBuffer::getWritePosition()
{
    return writePosition;
}