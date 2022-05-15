/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"

//==============================================================================
AnysynthAudioProcessor::AnysynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    attack1Time(.1f),
    decay1Time(.1f),
    sustain1Time(100.0f),
    release1Time(.1f),
    tree(*this, nullptr)
#endif
{
    NormalisableRange<float> attackParam(0.1f, 5000.0f);
    NormalisableRange<float> decayParam(0.1f, 5000.0f);
    NormalisableRange<float> sustainParam(0.1f, 100.0f); //%
    NormalisableRange<float> releaseParam(0.1f, 5000.0f);

    // osc attack
    tree.createAndAddParameter("attack1", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);

    // osc decay
    tree.createAndAddParameter("decay1", "Decay", "Decay", decayParam, 0.1f, nullptr, nullptr);

    // osc sustain
    tree.createAndAddParameter("sustain1", "Sustain", "Sustain", sustainParam, 100.0f, nullptr, nullptr);

    // osc release
    tree.createAndAddParameter("release1", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr);

    //========================================
    NormalisableRange<float> wavetypeParam(0, 4);
    tree.createAndAddParameter("wavetype", "WaveType", "wavetype", wavetypeParam, 0, nullptr, nullptr);

    //========================================
    NormalisableRange<float> filterTypeVal(0, 2);
    NormalisableRange<float> cutoffValParam(20.0f, 10000.0f);
    NormalisableRange<float> resValParam(1, 5);

    tree.createAndAddParameter("filterType", "FilterType", "filterType", filterTypeVal, 0, nullptr, nullptr);
    tree.createAndAddParameter("filterCutoff", "FilterCutoff", "filterCutoff", cutoffValParam, 400.0f, nullptr, nullptr);
    tree.createAndAddParameter("filterRes", "FilterRes", "filterRes", resValParam, 1, nullptr, nullptr);

    


    tree.state = ValueTree("Foo");
    anySynth.clearVoices();

    for (int i = 0; i < 16; ++i) {
        anySynth.addVoice(new SynthVoice());
    }

    anySynth.clearSounds();
    anySynth.addSound(new SynthSound());
}

AnysynthAudioProcessor::~AnysynthAudioProcessor()
{
}

//==============================================================================
const juce::String AnysynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AnysynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AnysynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AnysynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AnysynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AnysynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AnysynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AnysynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AnysynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void AnysynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AnysynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);

    lastSampleRate = sampleRate;
    anySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AnysynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AnysynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AnysynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    /*===========================================================================*/
    for (int i = 0; i < anySynth.getNumVoices(); ++i)
    {
        if (anySynthVoice = dynamic_cast<SynthVoice*>(anySynth.getVoice(i)))
        {
            float* attackFloatPtr = (float*)tree.getRawParameterValue("attack1");
            float* decayFloatPtr = (float*)tree.getRawParameterValue("decay1");
            float* sustainFloatPtr = (float*)tree.getRawParameterValue("sustain1");
            float* releaseFloatPtr = (float*)tree.getRawParameterValue("release1");

            anySynthVoice->getEnvelopeParams(attackFloatPtr, decayFloatPtr, sustainFloatPtr, releaseFloatPtr);

            //======================
            anySynthVoice->getOscType((float*)tree.getRawParameterValue("wavetype"));

            //======================
            float* filterTypePtr = (float*)tree.getRawParameterValue("filterType");
            float* filterCutoffPtr = (float*)tree.getRawParameterValue("filterCutoff");
            float* filterResPtr = (float*)tree.getRawParameterValue("filterRes");

            anySynthVoice->getFilterParams(filterTypePtr, filterCutoffPtr, filterResPtr);
        }
    }
    

    buffer.clear();

    anySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool AnysynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AnysynthAudioProcessor::createEditor()
{
    return new AnysynthAudioProcessorEditor (*this);
}

//==============================================================================
void AnysynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AnysynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AnysynthAudioProcessor();
}
