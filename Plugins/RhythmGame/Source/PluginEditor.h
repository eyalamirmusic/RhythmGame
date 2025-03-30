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
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor {processor};
};

} // namespace EA::GUI::Plugins::RhythmGame
