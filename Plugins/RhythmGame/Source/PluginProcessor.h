#pragma once

#include "Parameters.h"

namespace EA::Audio::Plugins::RhythmGame
{
class Processor : public ProcessorBase
{
public:
    Processor();

private:
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
};

} // namespace EA::Audio::Plugins::RhythmGame
