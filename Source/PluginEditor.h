/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./DialLookAndFeel/DialLookAndFeel.h"

//==============================================================================
/**
*/
class CompressorV1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CompressorV1AudioProcessorEditor (CompressorV1AudioProcessor&);
    ~CompressorV1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompressorV1AudioProcessor& audioProcessor;

    juce::Slider thresholdDial;
    juce::Slider ratioDial;
    juce::Slider attackDial;
    juce::Slider releaseDial;
    juce::Slider outputDial;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttachment;

    DialLookAndFeel dialLAF;

    juce::Label thresholdLabel;
    juce::Label ratioLabel;
    juce::Label attackLabel;
    juce::Label releaseLabel;
    juce::Label outputLabel;

    juce::DropShadow shadowProperties;
    juce::DropShadowEffect labelShadow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorV1AudioProcessorEditor)
};
