/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDoublerAudioProcessor::SimpleDoublerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
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

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleDoublerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDoublerAudioProcessor();
}
