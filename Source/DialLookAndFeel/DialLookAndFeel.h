/*
  ==============================================================================

    DialLookAndFeel.h
    Created: 2 Jul 2022 3:31:34pm
    Author:  tatao

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DialLookAndFeel : public juce::LookAndFeel_V4
{
public:
    DialLookAndFeel();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
};