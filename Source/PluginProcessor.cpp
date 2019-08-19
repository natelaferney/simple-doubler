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
			std::make_unique<AudioParameterBool> ("d1LeftActive", "Doubler 1 Left Active", true),
			std::make_unique<AudioParameterFloat> ("d1LeftGain", "Doubler 1 Left Gain", NormalisableRange<float>(-30.0f, 6.0f, 0.1f), -3.0f),
			std::make_unique<AudioParameterFloat> ("d1LeftPan", "Doubler 1 Left Pan", NormalisableRange<float>(0.0f, 100.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat> ("d1LeftDelay", "Doulber 1 Left Delay", NormalisableRange<float>(0.0f, 999.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterBool>("d1RightActive", "Doubler 1 Right Active", true),
			std::make_unique<AudioParameterFloat>("d1RightGain", "Doubler 1 Right Gain", NormalisableRange<float>(-30.0f, 6.0f, 0.1f), -3.0f),
			std::make_unique<AudioParameterFloat>("d1RightPan", "Doubler 1 Right Pan", NormalisableRange<float>(0.0f, 100.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("d1RightDelay", "Doulber 1 Right Delay", NormalisableRange<float>(0.0f, 999.0f, 1.0f), 0.0f)
		}),
	d1LeftBuffer(44100), d1RightBuffer(44100)
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
	d1LeftBuffer.reset();
	d1RightBuffer.reset();
	int currentSampleRate = (int)(sampleRate + .5);
	if (currentSampleRate != d1LeftBuffer.getSampleRate())
	{
		d1LeftBuffer.setSampleRate(currentSampleRate);
		d1LeftBuffer.resize(currentSampleRate);
	}
	if (currentSampleRate != d1RightBuffer.getSampleRate())
	{
		d1RightBuffer.setSampleRate(currentSampleRate);
		d1RightBuffer.resize(currentSampleRate);
	}
}

void SimpleDoublerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleDoublerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleDoublerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	const int bufferSize = buffer.getNumSamples();
	float tempLeft;
	float tempRight;
	float readLeft;
	float readRight;
	float sumLeft = 0;
	float sumRight = 0;

	const bool leftToggle1Value = (*d1LeftToggle < .5) ? false : true;
	const bool rightToggle1Value = (*d1RightToggle < .5) ? false : true;
	const float leftGain1Value = Decibels::decibelsToGain(*d1LeftGain);
	const float rightGain1Value = Decibels::decibelsToGain(*d1RightGain);
	const float leftPan1Value = *d1LeftPan;
	const float rightPan1Value = *d1RightPan;
	const float leftDelay1Value = *d1LeftDelay;
	const float rightDelay1Value = *d1RightDelay;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
	
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) buffer.clear (i, 0, bufferSize);
	d1LeftBuffer.setReadPositionFromMilliseconds(leftDelay1Value);
	d1RightBuffer.setReadPositionFromMilliseconds(rightDelay1Value);
	switch (totalNumInputChannels)
	{
	case 1:
		for (auto i = 0; i < bufferSize; ++i)
		{
			tempLeft = buffer.getSample(0, i);
			tempRight = buffer.getSample(0, i);
			d1LeftBuffer.write(tempLeft);
			d1RightBuffer.write(tempRight);
			//readLeft = (leftToggle1Value) ? leftGain1Value * d1LeftBuffer.read() : 0.0f;
			//readRight = (rightToggle1Value) ? rightGain1Value * d1RightBuffer.read() : 0.0f;
			//sumLeft = std::cos((pi / 4) - leftPan1Value * (pi / 4)) * readLeft + std::cos((pi / 4) + rightPan1Value * (pi / 4)) * readRight;
			//sumRight = std::sin((pi / 4) - leftPan1Value * (pi / 4)) * readLeft + std::sin((pi / 4) + leftPan1Value * (pi / 4)) * readRight;
			buffer.addSample(0, i, sumLeft);
			buffer.addSample(1, i, sumRight);
		}
		break;
	case 2:
		for (auto i = 0; i < bufferSize; ++i)
		{
			tempLeft = buffer.getSample(0, i);
			tempRight = buffer.getSample(1, i);
			d1LeftBuffer.write(tempLeft);
			d1RightBuffer.write(tempRight);
			//readLeft = (leftToggle1Value) ? leftGain1Value * d1LeftBuffer.read() : 0.0f;
			//readRight = (rightToggle1Value) ? rightGain1Value * d1RightBuffer.read() : 0.0f;
			//sumLeft = std::cos((pi / 4) - leftPan1Value * (pi / 4)) * readLeft + std::cos((pi / 4) + rightPan1Value * (pi / 4)) * readRight;
			//sumRight = std::sin((pi / 4) - leftPan1Value * (pi / 4)) * readLeft + std::sin((pi / 4) + rightPan1Value * (pi / 4)) * readRight;
			buffer.addSample(0, i, sumLeft);
			buffer.addSample(1, i, sumRight);
		}
		break;
	default:
		break;
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
	copyXmlToBinary(*xml, destData);
	delete xml;
}

void SimpleDoublerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	XmlElement * xmlState = getXmlFromBinary(data, sizeInBytes);
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

		parameters.getParameter("d1LeftActive")->beginChangeGesture();
		parameters.getParameter("d1RightActive")->beginChangeGesture();
		parameters.getParameter("d1LeftGain")->beginChangeGesture();
		parameters.getParameter("d1RightGain")->beginChangeGesture();
		parameters.getParameter("d1LeftPan")->beginChangeGesture();
		parameters.getParameter("d1RightPan")->beginChangeGesture();
		parameters.getParameter("d1LeftDelay")->beginChangeGesture();
		parameters.getParameter("d1RightDelay")->beginChangeGesture();

		parameters.getParameter("d1LeftActive")->setValueNotifyingHost(d1LeftToggleValue);
		parameters.getParameter("d1RightActive")->setValueNotifyingHost(d1RightToggleValue);
		parameters.getParameter("d1LeftGain")->setValueNotifyingHost(d1LeftGainValue);
		parameters.getParameter("d1RightGain")->setValueNotifyingHost(d1RightGainValue);
		parameters.getParameter("d1LeftPan")->setValueNotifyingHost(d1LeftPanValue);
		parameters.getParameter("d1RightPan")->setValueNotifyingHost(d1RightPanValue);
		parameters.getParameter("d1LeftDelay")->setValueNotifyingHost(d1LeftDelayValue);
		parameters.getParameter("d1RightDelay")->setValueNotifyingHost(d1RightDelayValue);

		parameters.getParameter("d1LeftActive")->endChangeGesture();
		parameters.getParameter("d1RightActive")->endChangeGesture();
		parameters.getParameter("d1LeftGain")->endChangeGesture();
		parameters.getParameter("d1RightGain")->endChangeGesture();
		parameters.getParameter("d1LeftPan")->endChangeGesture();
		parameters.getParameter("d1RightPan")->endChangeGesture();
		parameters.getParameter("d1LeftDelay")->endChangeGesture();
		parameters.getParameter("d1RightDelay")->endChangeGesture();
	}
	delete xmlState;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDoublerAudioProcessor();
}
