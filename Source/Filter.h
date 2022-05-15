/*
  ==============================================================================

    Filter.h
    Created: 13 March 2022 5:44:07pm
    Author:  derek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(AnysynthAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Slider filterCutoff;
    Slider filterRes;

    ComboBox filterMenu;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> cutoffValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resValue;

    AnysynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
