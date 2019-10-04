/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
SimpleDoublerAudioProcessorEditor::SimpleDoublerAudioProcessorEditor (SimpleDoublerAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);

	setLookAndFeel(&lookAndFeel);

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
	addAndMakeVisible(d1LeftLabel = new Label());
	d1LeftLabel->setBounds(400, 79, 100, 20);
	d1LeftLabel->setText("Left", dontSendNotification);
	addAndMakeVisible(d1RightLabel = new Label());
	d1RightLabel->setBounds(400, 209, 100, 20);
	d1RightLabel->setText("Right", dontSendNotification);
	addAndMakeVisible(dryGainSliderLabel = new Label());
	dryGainSliderLabel->setBounds(515, 110, 100, 20);
	dryGainSliderLabel->setText("Dry Gain", dontSendNotification);

	//d1 toggle left button
	addAndMakeVisible(d1LeftToggleButton = new TextButton());
	d1LeftToggleButton->setBounds(25, 75, 10, 10);
	d1LeftToggleButton->setClickingTogglesState(true);
	d1LeftToggleButton->setColour(TextButton::buttonOnColourId, Colours::limegreen);
	d1LeftToggleButton->setColour(TextButton::buttonColourId, Colours::darkslategrey);
	d1LeftToggleButtonAttachment.reset(new ButtonAttachment(valueTreeState, "d1LeftActive", *d1LeftToggleButton));


	//d1 gain left slider
	addAndMakeVisible(d1LeftGainSlider = new Slider());
	d1LeftGainSlider->setRange(-30.0f, 6.0f, 0.1f);
	d1LeftGainSlider->setValue(-12.0f);
	d1LeftGainSlider->setPopupMenuEnabled(false);
	d1LeftGainSlider->setSliderStyle(Slider::Rotary);
	d1LeftGainSlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1LeftGainSlider->setBounds(50, 50, 100, 100);
	d1LeftGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1LeftGainSlider->setTextValueSuffix(" dB");
	d1LeftGainSlider->setComponentID("d1LeftGainSlider");
	d1LeftGainSlider->addListener(this);
	d1LeftGainSliderAttachment.reset(new SliderAttachment(valueTreeState, "d1LeftGain", *d1LeftGainSlider));

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
	d1LeftPanningSlider->setComponentID("d1LeftPanningSlider");
	d1LeftPanningSlider->addListener(this);
	d1LeftPanningSliderAttachment.reset(new SliderAttachment(valueTreeState, "d1LeftPan", *d1LeftPanningSlider));

	//d1 delay left slider
	addAndMakeVisible(d1LeftDelaySlider = new Slider());
	d1LeftDelaySlider->setRange(0.0f, 200.0f, 1.0f);
	d1LeftDelaySlider->setValue(0.0f);
	d1LeftDelaySlider->setPopupMenuEnabled(false);
	d1LeftDelaySlider->setSliderStyle(Slider::Rotary);
	d1LeftDelaySlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1LeftDelaySlider->setBounds(300, 50, 100, 100);
	d1LeftDelaySlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1LeftDelaySlider->setTextValueSuffix(" mS");
	d1LeftDelaySlider->setComponentID("d1LeftDelaySlider");
	d1LeftDelaySlider->addListener(this);
	d1LeftDelaySliderAttachment.reset(new SliderAttachment(valueTreeState, "d1LeftDelay", *d1LeftDelaySlider));

	//d1 toggle right button
	addAndMakeVisible(d1RightToggleButton = new TextButton());
	d1RightToggleButton->setBounds(25, 202, 10, 10);
	d1RightToggleButton->setClickingTogglesState(true);
	d1RightToggleButton->setColour(TextButton::buttonOnColourId, Colours::limegreen);
	d1RightToggleButton->setColour(TextButton::buttonColourId, Colours::darkslategrey);
	d1RightToggleButtonAttachment.reset(new ButtonAttachment(valueTreeState, "d1RightActive", *d1RightToggleButton));

	//d1 gain right slider
	addAndMakeVisible(d1RightGainSlider = new Slider());
	d1RightGainSlider->setRange(-30.0f, 6.0f, 0.1f);
	d1RightGainSlider->setValue(-12.0f);
	d1RightGainSlider->setPopupMenuEnabled(false);
	d1RightGainSlider->setSliderStyle(Slider::Rotary);
	d1RightGainSlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1RightGainSlider->setBounds(52, 175, 100, 100);
	d1RightGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1RightGainSlider->setTextValueSuffix(" dB");
	d1RightGainSlider->setComponentID("d1RightGainSlider");
	d1RightGainSlider->addListener(this);
	d1RightGainSliderAttachment.reset(new SliderAttachment(valueTreeState, "d1RightGain", *d1RightGainSlider));

	//d1 pan right slider
	addAndMakeVisible(d1RightPanningSlider = new Slider());
	d1RightPanningSlider->setRange(0.0, 100.0, 1.0f);
	d1RightPanningSlider->setValue(0.0f);
	d1RightPanningSlider->setPopupMenuEnabled(false);
	d1RightPanningSlider->setSliderStyle(Slider::Rotary);
	d1RightPanningSlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1RightPanningSlider->setBounds(177, 175, 100, 100);
	d1RightPanningSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1RightPanningSlider->setTextValueSuffix(" %");
	d1RightPanningSlider->setComponentID("d1RightPanningSlider");
	d1RightPanningSlider->addListener(this);
	d1RightPanningSliderAttachment.reset(new SliderAttachment(valueTreeState, "d1RightPan", *d1RightPanningSlider));

	//d1 delay right slider
	addAndMakeVisible(d1RightDelaySlider = new Slider());
	d1RightDelaySlider->setRange(0.0f, 200.0f, 1.0f);
	d1RightDelaySlider->setValue(0.0f);
	d1RightDelaySlider->setPopupMenuEnabled(false);
	d1RightDelaySlider->setSliderStyle(Slider::Rotary);
	d1RightDelaySlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	d1RightDelaySlider->setBounds(302, 175, 100, 100);
	d1RightDelaySlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	d1RightDelaySlider->setTextValueSuffix(" mS");
	d1RightDelaySlider->setComponentID("d1RightDelaySlider");
	d1RightDelaySlider->addListener(this);
	d1RightDelaySliderAttachment.reset(new SliderAttachment(valueTreeState, "d1RightDelay", *d1RightDelaySlider));

	addAndMakeVisible(testLabel = new Label());
	testLabel->setBounds(420, 250, 80, 50);

	//sync button
	addAndMakeVisible(syncButton = new TextButton("SYNC"));
	syncButton->setBounds(10, 260, 40, 20);
	//syncButton->setClickingTogglesState(true);
	syncButton->setColour(TextButton::buttonColourId, Colours::darkgoldenrod);
	//syncButton->setColour(TextButton::buttonColourId, Colours::darkblue);
	syncButton->setComponentID("syncButton");
	syncButton->addListener(this);

	//dry gain slider
	addAndMakeVisible(dryGainSlider = new Slider());
	dryGainSlider->setRange(-120.0f, 0.0f, 0.1f);
	dryGainSlider->setValue(0.0f);
	dryGainSlider->setPopupMenuEnabled(false);
	dryGainSlider->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	dryGainSlider->setSliderStyle(Slider::Rotary);
	dryGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	dryGainSlider->setBounds(500, 150, 100, 100);
	dryGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	dryGainSlider->setTextValueSuffix(" dB");
	dryGainSliderAttachment.reset(new SliderAttachment(valueTreeState, "dryGain", *dryGainSlider));
}

SimpleDoublerAudioProcessorEditor::~SimpleDoublerAudioProcessorEditor()
{
	setLookAndFeel(nullptr);
}

//==============================================================================
void SimpleDoublerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	ColourGradient gradient = ColourGradient(Colours::slategrey, 250.0f, 150.0f, Colours::darkslategrey, 200.0f, 500.0f, false);
	g.setGradientFill(gradient);
	g.fillAll();
	testLabel->setText(juce::String(processor.getMainBusNumInputChannels()), dontSendNotification);
}

void SimpleDoublerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void SimpleDoublerAudioProcessorEditor::buttonClicked(Button * button)
{
	if (button->getComponentID() == "syncButton")
	{
		d1RightPanningSlider->setValue(d1LeftPanningSlider->getValue());
		d1RightGainSlider->setValue(d1LeftGainSlider->getValue());
		d1RightDelaySlider->setValue(d1LeftDelaySlider->getValue());
	}

}

void SimpleDoublerAudioProcessorEditor::sliderValueChanged(Slider * slider)
{

}