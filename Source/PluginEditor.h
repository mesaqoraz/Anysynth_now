/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"

//==============================================================================
/**
*/
class AnysynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AnysynthAudioProcessorEditor (AnysynthAudioProcessor&);
    ~AnysynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AnysynthAudioProcessor& audioProcessor;

    Oscillator oscGui;
    Envelope envGui;
    Filter filterGui;

    /*
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackTree1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackTree2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackTree3;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayTree1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayTree2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayTree3;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainTree1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainTree2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainTree3;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseTree1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseTree2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseTree3;

    Slider attackSlider1;
    Slider attackSlider2;
    Slider attackSlider3;

    Slider decaySlider1; //init
    Slider decaySlider2;
    Slider decaySlider3;

    Slider sustainSlider1; //init
    Slider sustainSlider2;
    Slider sustainSlider3;

    Slider releaseSlider1;
    Slider releaseSlider2;
    Slider releaseSlider3;
    */

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnysynthAudioProcessorEditor)
};
