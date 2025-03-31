#include "Oscillator.h"

namespace EA::Audio
{

void Phasor::setPitch(float freqHz, float sr) noexcept
{
    phaseDelta = 1.f / sr * freqHz;
}
void Phasor::reset() noexcept
{
    phase = 0.f;
}

float Phasor::getNextPhase() noexcept
{
    phase = fmod(phase + phaseDelta, 1.f);
    return phase;
}

void Oscillator::reset() noexcept
{
    phasor.reset();
}

void Oscillator::setPitch(const juce::MPENote& note, double sr) noexcept
{
    setPitch((float) note.getFrequencyInHertz(), (float) sr);
}

void Oscillator::setPitch(float freq, float sr) noexcept
{
    phasor.setPitch(freq, sr);
}
} // namespace EA::Audio