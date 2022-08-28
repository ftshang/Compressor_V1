/*
  ==============================================================================

    DialLookAndFeel.cpp
    Created: 2 Jul 2022 3:31:34pm
    Author:  tatao

  ==============================================================================
*/

#include "DialLookAndFeel.h"

DialLookAndFeel::DialLookAndFeel()
{

}

void DialLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    auto diameter = juce::jmin(width, height) * .74f;
    auto radius = diameter * 0.5f;
    auto centerX = x + width * 0.5f;
    auto centerY = y + height * 0.5f;
    auto rectangleX = centerX - radius;
    auto rectangleY = centerY - radius;
    auto angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    juce::Rectangle<float> dialArea(rectangleX, rectangleY, diameter, diameter);
    g.setColour(juce::Colours::darkred.brighter(0.61f)); // center color
    g.fillEllipse(dialArea);

    g.setColour(juce::Colours::black.withAlpha(0.1f)); // outline
    g.drawEllipse(rectangleX, rectangleY, diameter, diameter, 10.0f);

    juce::Path dialTick;
    g.setColour(juce::Colours::whitesmoke.darker(0.3f)); // tick color
    dialTick.addRoundedRectangle(0, -radius + 6, 5.88f, radius * 0.6, 5.f, 5.f, true, true, true, true);
    //dialTick.addRectangle(0, -radius + 6, 5.88f, radius * 0.6);
    //g.fillPath(dialTick);
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));

    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int>(-1, 4);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.9f);
    dialShadow.setShadowProperties(shadowProperties);

    slider.setComponentEffect(&dialShadow);
}