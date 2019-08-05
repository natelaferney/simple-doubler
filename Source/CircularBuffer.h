#pragma once
#include <vector>

class CircularBuffer
{
public:
	CircularBuffer(int sizeOfBuffer);
	void setSampleRate(int newSampleRate);
	void setReadPositionFromMilliseconds(int milliseconds);
	float read();
	void write(float val);
	void reset();
	~CircularBuffer();

private:
	int bufferSize;
	int readPosition;
	int writePosition;
	int offset;
	int sampleRate;
	std::vector<float> buffer;
};