#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::GUI::Plugins::RhythmGame
{
Editor::Editor(DSP::Processor& processorToUse)
    : AudioProcessorEditor(processorToUse)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void Editor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void Editor::resized()
{
    editor.setBounds(getLocalBounds());
}
} // namespace EA::GUI::Plugins::RhythmGame