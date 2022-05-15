/*
  ==============================================================================

    SynthVoice.h
    Created: 11 Mar 2022 5:56:11pm
    Author:  derek

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Maximilian/maximilian.h"

class SynthVoice : public SynthesiserVoice
{
    public:
        bool canPlaySound(SynthesiserSound* sound)
        {
            return !(dynamic_cast<SynthSound*>(sound) == nullptr);
        }

        /*===========================================================================*/

        void getOscType(float* selection)
        {
            osc1Wave = *selection;
        }

        double setOscType(string osc)
        {
            if (osc == "osc1") {
                switch (osc1Wave)
                {
                    case (0):
                        return osc1.sinewave(freq);
                        break;
                    case (1):
                        return osc1.saw(freq);
                        break;
                    case (2):
                        return osc1.square(freq);
                        break;
                    case (3):
                        return osc1.triangle(freq);
                        break;
                    case (4):
                        return osc1.noise();
                    default:
                        return osc1.sinewave(freq);
                }
            }
        }

        /*===========================================================================*/

        void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
        {
            env1.setAttack(double(*attack));
            env1.setDecay(double(*decay));
            env1.setSustain(double(*sustain));
            env1.setRelease(double(*release));

        }

        double setEnvelope()
        {
            return env1.adsr(setOscType("osc1"), env1.trigger) * lvl;
        }

        /*===========================================================================*/

        void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
        {
            filterChoice = *filterType;
            cutoff = *filterCutoff;
            resonance = *filterRes;

        }

        /*===========================================================================*/

        double setFilter()
        {
            if (filterChoice == 0)
            {
                return fil1.lores(setEnvelope(), cutoff, resonance);
            }
            else if (filterChoice == 1)
            {
                return fil1.hires(setEnvelope(), cutoff, resonance);
            }
            else if (filterChoice == 2)
            {
                return fil1.bandpass(setEnvelope(), cutoff, resonance);
            }
            else
            {
                return fil1.lores(setEnvelope(), cutoff, resonance);
            }
        }

        /*===========================================================================*/

        void startNote (int midiNoteNumber, float vel, SynthesiserSound* sound, int currentPitchWheelPosition)
        {
            env1.trigger = 1;

            lvl = vel;
            freq = MidiMessage::getMidiNoteInHertz(midiNoteNumber - 2, 440.0);
            juce::Logger::getCurrentLogger()->writeToLog(to_string((float)MidiMessage::getMidiNoteInHertz(midiNoteNumber)));
            //juce::Logger::getCurrentLogger()->writeToLog(to_string(MidiMessage::getMidiNoteName(midiNoteNumber, true, true, false)));
            
        }

        /*===========================================================================*/

        void stopNote(float vel, bool allowTailOff)
        {
            env1.trigger = 0;

            allowTailOff = true;

            if (vel == 0) 
            {
                clearCurrentNote();
            }
            
        }

        /*===========================================================================*/

        void pitchWheelMoved(int newPitchWheelValue)
        {

        }

        /*===========================================================================*/

        void controllerMoved(int ctrlrNumber, int newCtrlrValue)
        {

        }

        /*===========================================================================*/

        void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
        {
            //env1.setAttack(2000);
            //env1.setDecay(500);
            //env1.setSustain(0.85);
            //env1.setRelease(2000);


            for (int sample = 0; sample < numSamples; ++sample)
            {

                /*
                //double osc1Wave = osc1.pulse(freq, .25);
                double osc1Sound = env1.adsr(setOscType("osc1"), env1.trigger) * lvl;
                double osc1Filtered = fil1.lores(osc1Sound, 1200, 0.1);
                */



                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                {

                    outputBuffer.addSample(channel, startSample, setFilter());

                }

                ++startSample;
            }


        }

        /*===========================================================================*/

    private:
        double lvl;
        double freq;
        int osc1Wave;

        //oscillators
        maxiOsc osc1;
        maxiOsc osc2;
        maxiOsc osc3;
        maxiOsc osc4;

        //envelopes
        maxiEnv env1;
        maxiEnv env2;
        maxiEnv env3;
        maxiEnv env4;

        //filters
        maxiFilter fil1;
        maxiFilter fil2;
        maxiFilter fil3;
        maxiFilter fil4;
        maxiFilter fil5;
        
        int filterChoice;
        float cutoff;
        float resonance;

        //LFOs
        maxiOsc lfo1;
        maxiOsc lfo2;
        maxiOsc lfo3;
        maxiOsc lfo4;
        maxiOsc lfo5;

};