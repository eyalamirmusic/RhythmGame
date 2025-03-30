#pragma once

#include "Parameters.h"

namespace EA::Audio::Plugins::RhythmGame
{
class Processor : public ProcessorBase
{
public:
    Processor();

private:
    void processBlock(Buffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
};

} // namespace EA::Audio::Plugins::RhythmGame
