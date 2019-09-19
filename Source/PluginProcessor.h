/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularBuffer.h"

//==============================================================================
/**
*/
class SimpleDoublerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimpleDoublerAudioProcessor();
    ~SimpleDoublerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
	AudioProcessorValueTreeState parameters;
	CircularBuffer d1LeftBuffer0;
	CircularBuffer d1LeftBuffer1;
	CircularBuffer d1RightBuffer0;
	CircularBuffer d1RightBuffer1;
	float * d1LeftToggle;
	float * d1RightToggle;
	float * d1LeftGain;
	float * d1RightGain;
	float * d1LeftPan;
	float * d1RightPan;
	float * d1LeftDelay;
	float * d1RightDelay;
	float * dryGain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDoublerAudioProcessor)
};
