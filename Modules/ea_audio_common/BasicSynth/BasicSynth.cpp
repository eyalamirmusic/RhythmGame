#include "BasicSynth.h"
#include "../Buffers/Buffers.h"

namespace EA::Audio
{

void BasicSynthVoice::noteStarted()
{
    adsr.noteOn();
}

void BasicSynthVoice::noteStopped(bool allowTailOff)
{
    adsr.noteOff();

    if (!allowTailOff)
        clearCurrentNote();
}

void BasicSynthVoice::process(Buffer& buffer) noexcept
{
    auto channelData = buffer.getWritePointer(0);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        auto next = random.nextFloat();
        channelData[sample] = juce::jmap(next, -1.f, 1.f);
    }

    Buffers::copyToAllChannels(buffer);
    buffer.applyGain(0.3f);

    adsr.applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());

    if (!adsr.isActive())
        clearCurrentNote();
}

void BasicSynthVoice::prepare(double sr, int)
{
    adsr.setSampleRate(sr);
}

BasicSynth::BasicSynth()
{
    for (int index = 0; index < 4; ++index)
    {
        auto newVoice = new BasicSynthVoice();
        newVoice->voiceBuffer = &voiceBuffer;
        synthVoices.emplace_back(newVoice);
        addVoice(newVoice);
    }
}

void BasicSynth::prepare(int numChannels, double sr, int blockSize)
{
    voiceBuffer.setSize(numChannels, blockSize);
    setCurrentPlaybackSampleRate(sr);

    for (auto& voice: synthVoices)
        voice->prepare(sr, blockSize);
}

void BasicSynth::process(Buffer& buffer, const MidiBuffer& midi) noexcept
{
    renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
}
} // namespace EA::Audio