/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 Mar 2022 9:57:16am
    Author:  derek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//using namespace juce;

//==============================================================================
Oscillator::Oscillator(AnysynthAudioProcessor& p) :
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.addItem("Triangle", 4);
    oscMenu.addItem("Noise", 5);
    oscMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);

    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wavetype", oscMenu);

    

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{

}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(juce::ComboBox* box)
{

}