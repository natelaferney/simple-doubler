/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"

static const float pi = MathConstants<float>::pi;

//==============================================================================
SimpleDoublerAudioProcessor::SimpleDoublerAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
	parameters(*this, nullptr, Identifier("SimpleDoubler"),
		{
			std::make_unique<AudioParameterBool> ("d1LeftActive", "Doubler 1 Left Active", false),
			std::make_unique<AudioParameterFloat> ("d1LeftGain", "Doubler 1 Left Gain", NormalisableRange<float>(-30.0f, 6.0f, 0.1f), -12.0f),
			std::make_unique<AudioParameterFloat> ("d1LeftPan", "Doubler 1 Left Pan", NormalisableRange<float>(0.0f, 100.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat> ("d1LeftDelay", "Doulber 1 Left Delay", NormalisableRange<float>(0.0f, 999.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterBool>("d1RightActive", "Doubler 1 Right Active", false),
			std::make_unique<AudioParameterFloat>("d1RightGain", "Doubler 1 Right Gain", NormalisableRange<float>(-30.0f, 6.0f, 0.1f), -12.0f),
			std::make_unique<AudioParameterFloat>("d1RightPan", "Doubler 1 Right Pan", NormalisableRange<float>(0.0f, 100.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("d1RightDelay", "Doulber 1 Right Delay", NormalisableRange<float>(0.0f, 999.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("dryGain", "Dry Gain", NormalisableRange<float>(-90.0f, 0.0f, 0.1f), 0.0f)
		}),
	d1LeftBuffer0(44100), d1LeftBuffer1(44100), d1RightBuffer0(44100), d1RightBuffer1(44100)
{
	//parameters
	d1LeftToggle = parameters.getRawParameterValue("d1LeftActive");
	d1RightToggle = parameters.getRawParameterValue("d1RightActive");
	d1LeftGain = parameters.getRawParameterValue("d1LeftGain");
	d1RightGain = parameters.getRawParameterValue("d1RightGain");
	d1LeftPan = parameters.getRawParameterValue("d1LeftPan");
	d1RightPan = parameters.getRawParameterValue("d1RightPan");
	d1LeftDelay = parameters.getRawParameterValue("d1LeftDelay");
	d1RightDelay = parameters.getRawParameterValue("d1RightDelay");
	dryGain = parameters.getRawParameterValue("dryGain");
}

SimpleDoublerAudioProcessor::~SimpleDoublerAudioProcessor()
{
}

//==============================================================================
const String SimpleDoublerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleDoublerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDoublerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDoublerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleDoublerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleDoublerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleDoublerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDoublerAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleDoublerAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleDoublerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleDoublerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	int currentSampleRate = (int)(sampleRate + .5);
	if (currentSampleRate != d1LeftBuffer0.getSampleRate() || 
		currentSampleRate != d1LeftBuffer1.getSampleRate())
	{
		d1LeftBuffer0.setSampleRate(currentSampleRate);
		d1LeftBuffer0.resize(currentSampleRate);
		d1LeftBuffer1.setSampleRate(currentSampleRate);
		d1LeftBuffer1.resize(currentSampleRate);
	}
	if (currentSampleRate != d1RightBuffer0.getSampleRate() ||
		currentSampleRate != d1RightBuffer1.getSampleRate())
	{
		d1RightBuffer0.setSampleRate(currentSampleRate);
		d1RightBuffer0.resize(currentSampleRate);
		d1RightBuffer1.setSampleRate(currentSampleRate);
		d1RightBuffer1.resize(currentSampleRate);
	}
	d1LeftBuffer0.reset();
	d1LeftBuffer1.reset();
	d1RightBuffer0.reset();
	d1RightBuffer1.reset();
}

void SimpleDoublerAudioProcessor::releaseResources()
{
	d1LeftBuffer0.reset();
	d1LeftBuffer1.reset();
	d1RightBuffer0.reset();
	d1RightBuffer1.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleDoublerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;
	else return true;
}
#endif

void SimpleDoublerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	const int bufferSize = buffer.getNumSamples();

	//get parameter values
	const bool leftToggle1Value = (*d1LeftToggle < .5) ? false : true;
	const bool rightToggle1Value = (*d1RightToggle < .5) ? false : true;
	const float leftGain1Value = Decibels::decibelsToGain(*d1LeftGain);
	const float rightGain1Value = Decibels::decibelsToGain(*d1RightGain);
	const float leftPan1Value = *d1LeftPan / 100;
	const float rightPan1Value = *d1RightPan / 100;
	const float leftDelay1Value = *d1LeftDelay;
	const float rightDelay1Value = *d1RightDelay;
	const float dryGainValue = Decibels::decibelsToGain(*dryGain);
	
	//clear buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) buffer.clear (i, 0, bufferSize);

	//set read position
	d1LeftBuffer0.setReadPositionFromMilliseconds(leftDelay1Value);
	d1LeftBuffer1.setReadPositionFromMilliseconds(leftDelay1Value);
	d1RightBuffer0.setReadPositionFromMilliseconds(rightDelay1Value);
	d1RightBuffer1.setReadPositionFromMilliseconds(rightDelay1Value);

	//initialize constants
	float tempLeft;
	float tempRight;
	float readLeft0;
	float readLeft1;
	float readRight0;
	float readRight1;
	float sumLeft;
	float sumRight;

	//switch statement for mono and stereo configurations
	for (int i = 0; i < bufferSize; ++i)
	{
		switch (totalNumInputChannels)
		{
		case 1:
			//read the channels
			tempLeft = buffer.getSample(0, i) / 2.0f;
			tempRight = tempLeft;
			break;
		default:
			//read the channels
			tempLeft = buffer.getSample(0, i);
			tempRight = buffer.getSample(1, i);
			break;
		}
		//write to buffer
		d1LeftBuffer0.write(tempLeft);
		d1LeftBuffer1.write(tempRight);
		d1RightBuffer0.write(tempLeft);
		d1RightBuffer1.write(tempRight);

		//get read values from buffer
		readLeft0 = d1LeftBuffer0.read();
		readLeft1 = d1LeftBuffer1.read();
		readRight0 = d1RightBuffer0.read();
		readRight1 = d1RightBuffer1.read();

		//apply gain and panning to doubler left 1
		readLeft0 *= (leftToggle1Value) ? leftGain1Value : 0.0f;
		readLeft1 *= (leftToggle1Value) ? (1 - leftPan1Value) * leftGain1Value : 0.0f;

		//apply gain and panning doubler right 1
		readRight0 *= (rightToggle1Value) ? (1 - rightPan1Value) * rightGain1Value : 0.0f;
		readRight1 *= (rightToggle1Value) ? rightGain1Value : 0.0f;

		//apply gain and panning doubler right 1
		sumLeft = readLeft0 + readRight0 + (dryGainValue * tempLeft);
		sumRight = readLeft1 + readRight1 + (dryGainValue * tempRight);
		buffer.setSample(0, i, sumLeft);
		buffer.setSample(1, i, sumRight);
	}
}

//==============================================================================
bool SimpleDoublerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleDoublerAudioProcessor::createEditor()
{
    return new SimpleDoublerAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void SimpleDoublerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	XmlElement * xml = new XmlElement("SimpleDoublerPreset");
	xml->setAttribute(Identifier("d1LeftToggle"), (double)parameters.getParameter("d1LeftActive")->convertTo0to1(*d1LeftToggle));
	xml->setAttribute(Identifier("d1RightToggle"), (double)parameters.getParameter("d1RightActive")->convertTo0to1(*d1RightToggle));
	xml->setAttribute(Identifier("d1LeftGain"), (double)parameters.getParameter("d1LeftGain")->convertTo0to1(*d1LeftGain));
	xml->setAttribute(Identifier("d1RightGain"), (double)parameters.getParameter("d1RightGain")->convertTo0to1(*d1RightGain));
	xml->setAttribute(Identifier("d1LeftPan"), (double)parameters.getParameter("d1LeftPan")->convertTo0to1(*d1LeftPan));
	xml->setAttribute(Identifier("d1RightPan"), (double)parameters.getParameter("d1RightPan")->convertTo0to1(*d1RightPan));
	xml->setAttribute(Identifier("d1LeftDelay"), (double)parameters.getParameter("d1LeftDelay")->convertTo0to1(*d1LeftDelay));
	xml->setAttribute(Identifier("d1RightDelay"), (double)parameters.getParameter("d1RightDelay")->convertTo0to1(*d1RightDelay));
	xml->setAttribute(Identifier("dryGain"), (double)parameters.getParameter("dryGain")->convertTo0to1(*dryGain));
	copyXmlToBinary(*xml, destData);
	delete xml;
}

void SimpleDoublerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState != nullptr)
	{
		const float d1LeftToggleValue = (float)xmlState->getDoubleAttribute("d1LeftToggle", 1.0f);
		const float d1RightToggleValue = (float)xmlState->getDoubleAttribute("d1RightToggle", 1.0f);
		const float d1LeftGainValue = (float)xmlState->getDoubleAttribute("d1LeftGain", 0.0f);
		const float d1RightGainValue = (float)xmlState->getDoubleAttribute("d1RightGain", 0.0f);
		const float d1LeftPanValue = (float)xmlState->getDoubleAttribute("d1LeftPan", 0.0f);
		const float d1RightPanValue = (float)xmlState->getDoubleAttribute("d1RightPan", 0.0f);
		const float d1LeftDelayValue = (float)xmlState->getDoubleAttribute("d1LeftDelay", 0.0f);
		const float d1RightDelayValue = (float)xmlState->getDoubleAttribute("d1RightDelay", 0.0f);
		const float dryGainValue = (float)xmlState->getDoubleAttribute("dryGain", 1.0f);

		parameters.getParameter("d1LeftActive")->beginChangeGesture();
		parameters.getParameter("d1RightActive")->beginChangeGesture();
		parameters.getParameter("d1LeftGain")->beginChangeGesture();
		parameters.getParameter("d1RightGain")->beginChangeGesture();
		parameters.getParameter("d1LeftPan")->beginChangeGesture();
		parameters.getParameter("d1RightPan")->beginChangeGesture();
		parameters.getParameter("d1LeftDelay")->beginChangeGesture();
		parameters.getParameter("d1RightDelay")->beginChangeGesture();
		parameters.getParameter("dryGain")->beginChangeGesture();

		parameters.getParameter("d1LeftActive")->setValueNotifyingHost(d1LeftToggleValue);
		parameters.getParameter("d1RightActive")->setValueNotifyingHost(d1RightToggleValue);
		parameters.getParameter("d1LeftGain")->setValueNotifyingHost(d1LeftGainValue);
		parameters.getParameter("d1RightGain")->setValueNotifyingHost(d1RightGainValue);
		parameters.getParameter("d1LeftPan")->setValueNotifyingHost(d1LeftPanValue);
		parameters.getParameter("d1RightPan")->setValueNotifyingHost(d1RightPanValue);
		parameters.getParameter("d1LeftDelay")->setValueNotifyingHost(d1LeftDelayValue);
		parameters.getParameter("d1RightDelay")->setValueNotifyingHost(d1RightDelayValue);
		parameters.getParameter("dryGain")->setValueNotifyingHost(dryGainValue);

		parameters.getParameter("d1LeftActive")->endChangeGesture();
		parameters.getParameter("d1RightActive")->endChangeGesture();
		parameters.getParameter("d1LeftGain")->endChangeGesture();
		parameters.getParameter("d1RightGain")->endChangeGesture();
		parameters.getParameter("d1LeftPan")->endChangeGesture();
		parameters.getParameter("d1RightPan")->endChangeGesture();
		parameters.getParameter("d1LeftDelay")->endChangeGesture();
		parameters.getParameter("d1RightDelay")->endChangeGesture();
		parameters.getParameter("dryGain")->endChangeGesture();
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDoublerAudioProcessor();
}
