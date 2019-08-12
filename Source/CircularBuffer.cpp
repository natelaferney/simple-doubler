#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int sizeOfBuffer)
{
	buffer.resize(sizeOfBuffer, 0.0f);
	bufferSize = sizeOfBuffer;
	writePosition = 0;
	offset = 1;
	readPosition = (writePosition - offset) % bufferSize;
}

CircularBuffer::~CircularBuffer()
{
}

void CircularBuffer::resize(int newSize)
{
	buffer.clear();
	buffer.resize(newSize, 0.0f);
	bufferSize = newSize;
	writePosition = 0;
	readPosition = (writePosition - offset) % bufferSize;
}

void CircularBuffer::setSampleRate(int newSampleRate)
{
	sampleRate = newSampleRate;
}

void CircularBuffer::setReadPositionFromMilliseconds(int milliseconds)
{
	offset = (int)(((milliseconds / 1000) * sampleRate) + .5);
	readPosition = (writePosition - offset) % bufferSize;
}

float CircularBuffer::read()
{
	float ret = buffer[readPosition++];
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
	offset = 1;
	readPosition = (writePosition - offset) % bufferSize;
}

const int CircularBuffer::getSampleRate()
{
	return sampleRate;
}

const int CircularBuffer::getBufferSize()
{
	return bufferSize;
}