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
    ScrollingSequences seq {plugin.state};
    KeyboardHandling handling {plugin.state};
    ScoreDisplay score {plugin.state.score};

    // juce::GenericAudioProcessorEditor editor {processor};
};

} // namespace EA::GUI::Plugins::RhythmGame
