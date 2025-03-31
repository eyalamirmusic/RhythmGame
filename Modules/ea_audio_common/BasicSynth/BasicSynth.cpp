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
    osc.reset();
    adsr.setParameters(shared->adsr);
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
    osc.setPitch(getCurrentlyPlayingNote(), getSampleRate());

    auto& oscs = shared->oscs;

    switch (oscs.selected)
    {
        case BasicSynthOSCOptions::Sine:
            osc.process(oscs.sine, buffer);
            break;
        case BasicSynthOSCOptions::Square:
            osc.process(oscs.square, buffer);
            break;
        case BasicSynthOSCOptions::Saw:
            osc.process(oscs.saw, buffer);
            break;
        case BasicSynthOSCOptions::ReversedSaw:
            osc.process(oscs.reversedSaw, buffer);
            break;
        case BasicSynthOSCOptions::WhiteNoise:
            osc.process(oscs.noise, buffer);
            break;
    }

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