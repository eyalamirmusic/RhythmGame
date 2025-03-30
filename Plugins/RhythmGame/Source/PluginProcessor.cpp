#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::Audio::Plugins::RhythmGame
{
Processor::Processor()
{
}

void Processor::processBlock(juce::AudioBuffer<float>& buffer,
                             juce::MidiBuffer& midiMessages)

{
    juce::ignoreUnused(midiMessages, buffer);
}

juce::AudioProcessorEditor* Processor::createEditor()
{
    return new GUI::Plugins::RhythmGame::Editor(*this);
}

} // namespace EA::Audio::Plugins::RhythmGame

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EA::Audio::Plugins::RhythmGame::Processor();
}