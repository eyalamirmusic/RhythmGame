#include "BasicSynth.h"
#include "../Buffers/Buffers.h"

namespace EA::Audio::BasicSynth
{

BasicSynthShared::BasicSynthShared()
{
    adsr.attack = 0.0001f;
    adsr.decay = 100.f;
    adsr.sustain = 1.f;
    adsr.release = 0.001f;
}

void Voice::noteStarted()
{
    osc.reset();
    adsr.setParameters(shared->adsr);
    adsr.noteOn();
}

void Voice::noteStopped(bool allowTailOff)
{
    adsr.noteOff();

    if (!allowTailOff)
        clearCurrentNote();
}

void Voice::process(Buffer& buffer) noexcept
{
    osc.setPitch(getCurrentlyPlayingNote(), getSampleRate());

    auto& oscs = shared->oscs;

    switch (oscs.selected)
    {
        case OSCOptions::Sine:
            osc.process(oscs.sine, buffer);
            break;

        case OSCOptions::Square:
            osc.process(oscs.square, buffer);
            break;

        case OSCOptions::Saw:
            osc.process(oscs.saw, buffer);
            break;

        case OSCOptions::ReversedSaw:
            osc.process(oscs.reversedSaw, buffer);
            break;

        case OSCOptions::WhiteNoise:
            osc.process(oscs.noise, buffer);
            break;
    }

    adsr.applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());

    if (!adsr.isActive())
        clearCurrentNote();
}

void Voice::prepare(double sr, int)
{
    adsr.setSampleRate(sr);
}

Synth::Synth()
{
    for (auto& voice: synthVoices)
        voice->shared = &shared;
}
} // namespace EA::Audio::BasicSynth