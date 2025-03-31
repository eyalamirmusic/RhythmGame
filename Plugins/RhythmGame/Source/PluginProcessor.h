#pragma once

#include "Parameters.h"

namespace EA::Audio::Plugins::RhythmGame
{
class Processor : public ProcessorBase
{
public:
    Processor();

private:
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(Buffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;

    juce::AudioParameterChoice* oscillator = new juce::AudioParameterChoice(
        {"OSC", 1}, "OSC", {"Sine", "Square", "Saw", "Reversed Saw", "Noise"}, 0);

    BasicSynthShared shared;
    BasicSynth synth;
};

} // namespace EA::Audio::Plugins::RhythmGame
