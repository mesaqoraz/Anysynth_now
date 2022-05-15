/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
/*
void mySetSlider(string typeSlider, Slider* slider) {
    if (typeSlider == "attack") {
        slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
        slider.setRange(0.1f, 5000.0f);
        slider.setValue(0.1f);
        //slider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
      
    }
}
//*/

AnysynthAudioProcessorEditor::AnysynthAudioProcessorEditor(AnysynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), oscGui(p), envGui(p), filterGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);

    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&filterGui);

    /*
    // attack1
    attackSlider1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    attackSlider1.setRange(0.1f, 5000.0f);
    attackSlider1.setValue(0.1f);
    //attackSlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider1.addListener(this);
    addAndMakeVisible(&attackSlider1);

    // decay1
    decaySlider1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    decaySlider1.setRange(0.1f, 5000.0f);
    decaySlider1.setValue(0.1f);
    //decaySlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    decaySlider1.addListener(this);
    addAndMakeVisible(&decaySlider1);

    // attack1
    sustainSlider1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    sustainSlider1.setRange(0.1f, 5000.0f);
    sustainSlider1.setValue(0.1f);
    //sustainSlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    sustainSlider1.addListener(this);
    addAndMakeVisible(&sustainSlider1);

    //release1
    releaseSlider1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    releaseSlider1.setRange(0.1f, 5000.0f);
    releaseSlider1.setValue(0.1f);
    //attackSlider1.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    releaseSlider1.addListener(this);
    addAndMakeVisible(&releaseSlider1);

    attackTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "attack1", attackSlider1);

    decayTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "decay1", decaySlider1);

    sustainTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "sustain1", sustainSlider1);

    releaseTree1 = new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        "release1", releaseSlider1);
    */
}

AnysynthAudioProcessorEditor::~AnysynthAudioProcessorEditor()
{
}

//==============================================================================
void AnysynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AnysynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
}

/*
void AnysynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
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
//}