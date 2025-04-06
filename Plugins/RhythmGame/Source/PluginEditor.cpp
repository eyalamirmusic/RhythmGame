#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::GUI::Plugins::RhythmGame
{
Editor::Editor(DSP::Processor& processorToUse)
    : AudioProcessorEditor(processorToUse)
    , plugin(processorToUse)
{
    addAndMakeVisible(seq);
    addAndMakeVisible(handling);
    addAndMakeVisible(score);
    setResizable(true, true);
    setSize(400, 300);
}

void Editor::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void Editor::resized()
{
    handling.setBounds(getLocalBounds());
    Scaling::scale(seq, {0.f, 0.f, 1.f, 0.8f});
    Scaling::scale(score, {0.f, 0.8f, 1.f, 0.2f});
}
} // namespace EA::GUI::Plugins::RhythmGame