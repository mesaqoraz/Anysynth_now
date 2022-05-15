/*
  ==============================================================================

    Filter.cpp
    Created: 13 March 2022 5:44:08pm
    Author:  derek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(AnysynthAudioProcessor& p) :
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);

    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);

    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "filterType", filterMenu);

    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 10000.0);
    filterCutoff.setValue(400.0);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterCutoff);
    cutoffValue = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "filterCutoff", filterCutoff);

    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterRes);
    resValue = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "filterRes", filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    /*
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Filter", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    */

    g.fillAll(Colours::black);
}

void Filter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);

}
