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

} // namespace EA::Audio