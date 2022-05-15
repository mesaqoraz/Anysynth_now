/*
  ==============================================================================

    Envelope.cpp
    Created: 11 Mar 2022 4:50:46pm
    Author:  derek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(AnysynthAudioProcessor& p) :
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 200);
 
    // attack1
    attackSlider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider1.setRange(0.1f, 5000.0f);
    attackSlider1.setValue(0.1f);
    //attackSlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //attackSlider1.addListener(this);
    addAndMakeVisible(&attackSlider1);

    // decay1
    decaySlider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider1.setRange(0.1f, 5000.0f);
    decaySlider1.setValue(0.1f);
    //decaySlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //decaySlider1.addListener(this);
    addAndMakeVisible(&decaySlider1);

    // attack1
    sustainSlider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider1.setRange(0.1f, 5000.0f);
    sustainSlider1.setValue(0.1f);
    //sustainSlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //sustainSlider1.addListener(this);
    addAndMakeVisible(&sustainSlider1);

    //release1
    releaseSlider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider1.setRange(0.1f, 5000.0f);
    releaseSlider1.setValue(0.1f);
    //attackSlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    //releaseSlider1.addListener(this);
    addAndMakeVisible(&releaseSlider1);

    attackTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "attack1", attackSlider1);

    decayTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "decay1", decaySlider1);

    sustainTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "sustain1", sustainSlider1);

    releaseTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "release1", releaseSlider1);
    

}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    
    //g.fillAll(Colours::whitesmoke);

    Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::whitesmoke);
    g.setColour(Colours::black);
    g.drawText("Envelope", titleArea, Justification::centredTop);

    /*
    g.drawText("A")
    */

    Rectangle<float> area(25, 25, 150, 150);

    g.setColour(Colours::navy);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    /*
    Rectangle<int> area = getLocalBounds().reduced(40);


    attackSlider1.setBounds(10, 10, 40, 100);

    decaySlider1.setBounds(60, 10, 40, 100);

    sustainSlider1.setBounds(110, 10, 40, 100);

    releaseSlider1.setBounds(160, 10, 40, 100);
    */

    //Rectangle<int> area = getLocalBounds().reduced(40);

    Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    //
    attackSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

/*
void Envelope::sliderValueChanged(Slider* slider)
{


    /*
    if (slider == &attackSlider1)
    {
        audioProcessor.attack1Time = attackSlider1.getValue();
    }

    if (slider == &decaySlider1)
    {
        audioProcessor.decay1Time = decaySlider1.getValue();
    }

    if (slider == &sustainSlider1)
    {
        audioProcessor.sustain1Time = sustainSlider1.getValue();
    }

    if (slider == &releaseSlider1)
    {
        audioProcessor.release1Time = releaseSlider1.getValue();
    }
    */
//}*/