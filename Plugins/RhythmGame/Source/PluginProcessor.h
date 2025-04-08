#pragma once

#include "Parameters.h"
#include <ea_game_sequencer/ea_game_sequencer.h>

namespace EA::Audio::Plugins::RhythmGame
{

class Processor : public ProcessorBase
{
public:
    Processor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(Buffer&, MidiBuffer&) override;

    juce::AudioPlayHead* getActivePlayhead() const;


    AudioProcessorEditor* createEditor() override;

    Parameters params;

    SmoothGain gain;
    BasicSynth::Synth synth;
    Transport transport;

    Sequencer::GameState state;
    Sequencer::MultiPlayer player;

};

} // namespace EA::Audio::Plugins::RhythmGame
