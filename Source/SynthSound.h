/*
  ==============================================================================

    SynthSound.h
    Created: 11 Mar 2022 5:55:59pm
    Author:  derek

  ==============================================================================
*/

#pragma once
using namespace juce;
#include "../JuceLibraryCode/JuceHeader.h"



class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }

    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};