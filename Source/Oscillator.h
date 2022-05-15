/*
  ==============================================================================

    Oscillator.h
    Created: 12 Mar 2022 9:57:15am
    Author:  derek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component,
    private juce::ComboBox::Listener
{
public:
    Oscillator(AnysynthAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    virtual void comboBoxChanged(juce::ComboBox*) override;

private:
    juce::ComboBox oscMenu; 

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;


    AnysynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
