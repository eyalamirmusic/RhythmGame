#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::GUI::Plugins::RhythmGame
{
Editor::Editor(DSP::Processor& processorToUse)
    : AudioProcessorEditor(processorToUse)
    , plugin(processorToUse)
{
    addAndMakeVisible(seq);
    addAndMakeVisible(genericEditor);
    setResizable(true, true);
    setSize(400, 300);
}

void Editor::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void Editor::resized()
{
    genericEditor.setBoundsRelative(0.f, 0.f, 1.f, 0.5f);
    seq.setBoundsRelative(0.f, 0.5f, 1.f, 0.5f);
}
} // namespace EA::GUI::Plugins::RhythmGame