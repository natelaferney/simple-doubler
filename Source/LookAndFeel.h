#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SimpleDoublerLookAndFeel : public LookAndFeel_V4
{
public:
	SimpleDoublerLookAndFeel();
	//~DecibelKnobLookAndFeel();
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
private:
};
