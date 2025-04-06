#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace EA::Audio::Plugins::RhythmGame
{
Processor::Processor()
{
    params.addTo(*this);

    seq.sequenceTime = 16.0;
    auto& newSeq = seq.sequences.createNew();

    newSeq.duration = 16.0;

    auto note = Sequencer::TimedNote();
    auto start = 0.0;
    note.time.length = 0.5;

    for (int index = 0; index < 64; ++index)
    {
        note->noteNum = 42;

        note.time.start = start;
        start += 1.0;

        newSeq.create(note);
    }
}

void Processor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.prepare(getTotalNumOutputChannels(), sampleRate, samplesPerBlock);
    gain.prepare(sampleRate);
    transport.bpm = 100.0;
    transport.prepare(sampleRate, samplesPerBlock);
    transport.playing = true;
}

void Processor::processBlock(Buffer& buffer, MidiBuffer& midiMessages)

{
    auto noDenormals = juce::ScopedNoDenormals();
    buffer.clear();
    midiMessages.clear();

    transport.process(getActivePlayhead(), buffer.getNumSamples());

    player.process(seq, midiMessages, transport);

    synth.shared.filter.cutoff = params.cutoff->get();
    synth.shared.filter.reso = params.reso->get();
    synth.shared.oscs.selected = (BasicSynth::OSCOptions) params.oscillator->getIndex();
    synth.process(buffer, midiMessages);
    gain.process(buffer, params.volume->get());

    Buffers::clip(buffer);
}

juce::AudioPlayHead* Processor::getActivePlayhead() const
{
    if (Platform::isStandalone())
        return nullptr;

    return getPlayHead();
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