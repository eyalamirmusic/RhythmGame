#pragma once

#include "Parameters.h"
#include <ea_game_sequencer/ea_game_sequencer.h>

namespace EA::Audio::Plugins::RhythmGame
{
class Processor : public ProcessorBase
{
public:
    Processor();

private:
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(Buffer&, MidiBuffer&) override;

    juce::AudioPlayHead* getActivePlayhead() const;

    AudioProcessorEditor* createEditor() override;

    ChoiceParam* oscillator = new ChoiceParam(
        {"OSC", 1}, "OSC", {"Sine", "Square", "Saw", "Reversed Saw", "Noise"}, 0);
    FloatParam* volume = new FloatParam({"Volume", 1}, "Volume", 0.f, 0.5f, 0.25f);
    FloatParam* cutoff = new FloatParam({"Cutoff", 1}, "Cutoff", 100.f, 20000.f, 10000.f);
    FloatParam* reso = new FloatParam({"Reso", 1}, "Reso", 0.01f, 3.f, 1.f);


    SmoothGain gain;
    BasicSynth::Synth synth;
    Transport transport;
    Sequencer::Player player {Files::getDesktop() / "MIDI" / "bwv772.mid"};
};

} // namespace EA::Audio::Plugins::RhythmGame
