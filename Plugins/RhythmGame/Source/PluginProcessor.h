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

    ChoiceParam* oscillator = new ChoiceParam(
        {"OSC", 1}, "OSC", {"Sine", "Square", "Saw", "Reversed Saw", "Noise"}, 0);
    FloatParam* volume = new FloatParam({"Volume", 1}, "Volume", 0.f, 0.5f, 0.25f);

    SmoothGain gain;
    BasicSynth::Synth synth;
    Transport transport;
    Sequencer::Player player {Files::getDesktop() / "MIDI" / "bwv772.mid"};
};

} // namespace EA::Audio::Plugins::RhythmGame
