#pragma once

#include "PluginProcessor.h"

namespace EA::GUI::Plugins::RhythmGame
{
namespace DSP = Audio::Plugins::RhythmGame;

class Editor : public juce::AudioProcessorEditor
{
public:
    explicit Editor(DSP::Processor& processorToUse);

private:
    void paint(Graphics&) override;
    void resized() override;

    DSP::Processor& plugin;

    BasicWindow<juce::GenericAudioProcessorEditor> genericEditor {"Controls", plugin};
    BasicWindow<CPUUsage> usage {"CPU", plugin.measurer};
    ScrollingSequences seq {plugin.seq};

    // juce::GenericAudioProcessorEditor editor {processor};
};

} // namespace EA::GUI::Plugins::RhythmGame
