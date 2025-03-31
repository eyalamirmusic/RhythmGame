#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::Audio::Plugins::RhythmGame
{
Processor::Processor()
{
    addParameter(oscillator);

    for (auto& voice: synth.synthVoices)
        voice->shared = &shared;
}
void Processor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.prepare(getTotalNumOutputChannels(), sampleRate, samplesPerBlock);
}

void Processor::processBlock(Buffer& buffer, MidiBuffer& midiMessages)

{
    auto noDenormals = juce::ScopedNoDenormals();

    shared.oscs.selected = (BasicSynthOSCOptions)oscillator->getIndex();
    synth.process(buffer, midiMessages);
}

AudioProcessorEditor* Processor::createEditor()
{
    return new GUI::Plugins::RhythmGame::Editor(*this);
}

} // namespace EA::Audio::Plugins::RhythmGame

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EA::Audio::Plugins::RhythmGame::Processor();
}