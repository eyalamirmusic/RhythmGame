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
    ScrollingSequences seq {plugin.seq, plugin.userScore};
    KeyboardHandling handling {*plugin.seq.sequences[0], plugin.userScore};
    ScoreDisplay score {plugin.userScore};

    // juce::GenericAudioProcessorEditor editor {processor};
};

} // namespace EA::GUI::Plugins::RhythmGame
