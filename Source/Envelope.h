/*
  ==============================================================================

    Envelope.h
    Created: 11 Mar 2022 4:50:46pm
    Author:  derek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(AnysynthAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

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
    

    AnysynthAudioProcessor& audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
