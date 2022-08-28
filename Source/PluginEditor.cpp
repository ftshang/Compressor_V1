/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorV1AudioProcessorEditor::CompressorV1AudioProcessorEditor (CompressorV1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 400);

    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int>(-1, 4);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.9f);
    labelShadow.setShadowProperties(shadowProperties);

    addAndMakeVisible(thresholdDial);
    thresholdDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 72, 36);
    thresholdDial.setLookAndFeel(&dialLAF);
    thresholdDial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    thresholdDial.setTextValueSuffix(" dB");
    thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "threshold", thresholdDial);

    addAndMakeVisible(thresholdLabel);
    thresholdLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    thresholdLabel.setJustificationType(juce::Justification::centred);
    thresholdLabel.setComponentEffect(&labelShadow);

    addAndMakeVisible(ratioDial);
    ratioDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 72, 36);
    ratioDial.setLookAndFeel(&dialLAF);
    ratioDial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    ratioAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio", ratioDial);

    addAndMakeVisible(ratioLabel);
    ratioLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    ratioLabel.setJustificationType(juce::Justification::centred);
    ratioLabel.setComponentEffect(&labelShadow);

    addAndMakeVisible(attackDial);
    attackDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 72, 36);
    attackDial.setLookAndFeel(&dialLAF);
    attackDial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    attackDial.setTextValueSuffix(" ms");
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack", attackDial);

    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    attackLabel.setComponentEffect(&labelShadow);

    addAndMakeVisible(releaseDial);
    releaseDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 72, 36);
    releaseDial.setLookAndFeel(&dialLAF);
    releaseDial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    releaseDial.setTextValueSuffix(" ms");
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release", releaseDial);

    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setComponentEffect(&labelShadow);

    addAndMakeVisible(outputDial);
    outputDial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 72, 36);
    outputDial.setLookAndFeel(&dialLAF);
    outputDial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    outputDial.setTextValueSuffix(" dB");
    outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "output", outputDial);

    addAndMakeVisible(outputLabel);
    outputLabel.setText("Output", juce::NotificationType::dontSendNotification);
    outputLabel.setJustificationType(juce::Justification::centred);
    outputLabel.setComponentEffect(&labelShadow);
}

CompressorV1AudioProcessorEditor::~CompressorV1AudioProcessorEditor()
{
    thresholdDial.setLookAndFeel(nullptr);
    ratioDial.setLookAndFeel(nullptr);
    attackDial.setLookAndFeel(nullptr);
    releaseDial.setLookAndFeel(nullptr);
    outputDial.setLookAndFeel(nullptr);
}

//==============================================================================
void CompressorV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();

    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(139, 0, 0),
        400,
        juce::Colours::antiquewhite.brighter(0.9f),
        .5));

    g.fillRect(background);
}


void CompressorV1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    const auto leftMargin = getWidth() * 0.001f;
    const auto topMargin = getHeight() * 0.27f;
    const auto dialSize = getWidth() * 0.20f;

    thresholdDial.setBounds(leftMargin, topMargin, dialSize, dialSize);
    ratioDial.setBounds(thresholdDial.getX() + thresholdDial.getWidth(), topMargin, dialSize, dialSize);
    attackDial.setBounds(ratioDial.getX() + ratioDial.getWidth(), topMargin, dialSize, dialSize);
    releaseDial.setBounds(attackDial.getX() + attackDial.getWidth(), topMargin, dialSize, dialSize);
    outputDial.setBounds(releaseDial.getX() + releaseDial.getWidth(), topMargin, dialSize, dialSize);

    thresholdLabel.setBounds(leftMargin, thresholdDial.getY() + thresholdDial.getHeight(), dialSize, 32);
    ratioLabel.setBounds(thresholdLabel.getX() + thresholdLabel.getWidth(), ratioDial.getY() + ratioDial.getHeight(), dialSize, 32);
    attackLabel.setBounds(ratioLabel.getX() + ratioLabel.getWidth(), attackDial.getY() + attackDial.getHeight(), dialSize, 32);
    releaseLabel.setBounds(attackLabel.getX() + attackLabel.getWidth(), releaseDial.getY() + releaseDial.getHeight(), dialSize, 32);
    outputLabel.setBounds(releaseLabel.getX() + releaseLabel.getWidth(), outputDial.getY() + outputDial.getHeight(), dialSize, 32);
}
