#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::GUI::Plugins::RhythmGame
{
Editor::Editor(DSP::Processor& processorToUse)
    : AudioProcessorEditor(processorToUse)
    , plugin(processorToUse)
{
    addAndMakeVisible(seq);
    setResizable(true, true);
    setSize(400, 300);
}

void Editor::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void Editor::resized()
{
    seq.setBounds(getLocalBounds());
}
} // namespace EA::GUI::Plugins::RhythmGame