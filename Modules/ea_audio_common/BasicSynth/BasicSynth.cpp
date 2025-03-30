#include "BasicSynth.h"
#include "../Buffers/Buffers.h"

namespace EA::Audio
{

void WhiteNoise::processChannel(float* channelData, int numSamples) noexcept
{
    for (int sample = 0; sample < numSamples; ++sample)
    {
        auto next = random.nextFloat();
        channelData[sample] = juce::jmap(next, -1.f, 1.f);
    }
}

void WhiteNoise::process(Buffer& buffer) noexcept
{
    processChannel(buffer.getWritePointer(0), buffer.getNumSamples());
    Buffers::copyToAllChannels(buffer);
}

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
    whiteNoise.process(buffer);
    buffer.applyGain(0.3f);

    adsr.applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());

    if (!adsr.isActive())
        clearCurrentNote();
}

void BasicSynthVoice::prepare(double sr, int)
{
    adsr.setSampleRate(sr);
}

} // namespace EA::Audio