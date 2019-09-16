/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "LookAndFeel.h"

typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
*/
class SimpleDoublerAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener, public Button::Listener
{
public:
    SimpleDoublerAudioProcessorEditor (SimpleDoublerAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~SimpleDoublerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void buttonClicked(Button * button);
	void sliderValueChanged(Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDoublerAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;
	ScopedPointer<TextButton> d1LeftToggleButton;
	ScopedPointer<ButtonAttachment> d1LeftToggleButtonAttachment;
	ScopedPointer<TextButton> d1RightToggleButton;
	ScopedPointer<ButtonAttachment> d1RightToggleButtonAttachment;
	ScopedPointer<Slider> d1LeftGainSlider;
	ScopedPointer<SliderAttachment> d1LeftGainSliderAttachment;
	ScopedPointer<Slider> d1RightGainSlider;
	ScopedPointer<SliderAttachment> d1RightGainSliderAttachment;
	ScopedPointer<Slider> d1LeftPanningSlider;
	ScopedPointer<SliderAttachment> d1LeftPanningSliderAttachment;
	ScopedPointer<Slider> d1RightPanningSlider;
	ScopedPointer<SliderAttachment> d1RightPanningSliderAttachment;
	ScopedPointer<Slider> d1LeftDelaySlider;
	ScopedPointer<SliderAttachment> d1LeftDelaySliderAttachment;
	ScopedPointer<Slider> d1RightDelaySlider;
	ScopedPointer<SliderAttachment> d1RightDelaySliderAttachment;
	ScopedPointer<Label> gainLabel;
	ScopedPointer<Label> panLabel;
	ScopedPointer<Label> delayLabel;
	ScopedPointer<Label> d1LeftLabel;
	ScopedPointer<Label> d1RightLabel;
	ScopedPointer<Label> testLabel;
	SimpleDoublerLookAndFeel lookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDoublerAudioProcessorEditor)
};
