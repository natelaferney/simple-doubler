//#pragma once
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
	void resize(int newSize);
	const int getSampleRate();
	const int getBufferSize();
    int getReadPosition();
    int getWritePosition();
	~CircularBuffer();

private:
	int bufferSize;
	int readPosition;
	int writePosition;
	int sampleRate;
	std::vector<float> buffer;
};