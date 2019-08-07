/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDoublerAudioProcessorEditor::SimpleDoublerAudioProcessorEditor (SimpleDoublerAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);

	//labels
	addAndMakeVisible(gainLabel = new Label());
	gainLabel->setBounds(80, 10, 50, 20);
	gainLabel->setText("Gain", dontSendNotification);
	addAndMakeVisible(panLabel = new Label());
	panLabel->setBounds(196, 10, 100, 20);
	panLabel->setText("Panning", dontSendNotification);
	addAndMakeVisible(delayLabel = new Label());
	delayLabel->setBounds(328, 10, 100, 20);
	delayLabel->setText("Delay", dontSendNotification);

	//d1 toggle left button
	addAndMakeVisible(d1LeftToggleButton = new TextButton());
	d1LeftToggleButton->setBounds(25, 75, 10, 10);
	d1LeftToggleButton->setClickingTogglesState(true);
	d1LeftToggleButton->setColour(TextButton::buttonOnColourId, Colours::green);

	//d1 gain left slider
	addAndMakeVisible(d1LeftGainSlider = new Slider());
	d1LeftGainSlider->setRange(-30.0f, 6.0f, 0.1f);
	d1LeftGainSlider->setValue(-3.0f);
	d1LeftGainSlider->setPopupMenuEnabled(false);
	d1LeftGainSlider->setSliderStyle(Slider::Rotary);
	d1LeftGainSlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1LeftGainSlider->setBounds(50, 50, 100, 100);
	d1LeftGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1LeftGainSlider->setTextValueSuffix(" dB");

	//d1 pan left slider
	addAndMakeVisible(d1LeftPanningSlider = new Slider());
	d1LeftPanningSlider->setRange(0.0, 100.0, 1.0f);
	d1LeftPanningSlider->setValue(0.0f);
	d1LeftPanningSlider->setPopupMenuEnabled(false);
	d1LeftPanningSlider->setSliderStyle(Slider::Rotary);
	d1LeftPanningSlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1LeftPanningSlider->setBounds(175, 50, 100, 100);
	d1LeftPanningSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1LeftPanningSlider->setTextValueSuffix(" %");

	//d1 delay left slider
	addAndMakeVisible(d1LeftDelaySlider = new Slider());
	d1LeftDelaySlider->setRange(0.0f, 999.0f, 1.0f);
	d1LeftDelaySlider->setValue(0.0f);
	d1LeftDelaySlider->setPopupMenuEnabled(false);
	d1LeftDelaySlider->setSliderStyle(Slider::Rotary);
	d1LeftDelaySlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1LeftDelaySlider->setBounds(300, 50, 100, 100);
	d1LeftDelaySlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1LeftDelaySlider->setTextValueSuffix(" mS");
}

SimpleDoublerAudioProcessorEditor::~SimpleDoublerAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDoublerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SimpleDoublerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void SimpleDoublerAudioProcessorEditor::buttonClicked(Button * button)
{

}