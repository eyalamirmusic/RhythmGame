#pragma once

#include "../Buffers/Buffers.h"

namespace EA::Audio
{
class Phasor
{
public:
    void setPitch(float freqHz, float sr) noexcept;
    void reset() noexcept;
    float getNextPhase() noexcept;

private:
    float phase = 0.f;
    float phaseDelta = 0.f;
};

class Oscillator
{
public:
    void reset() noexcept;

    void setPitch(const juce::MPENote& note, double sr) noexcept;

    void setPitch(float freq, float sr) noexcept;

    template <typename Generator>
    void process(Generator& generator, float* data, int numSamples) noexcept
    {
        for (int sample = 0; sample < numSamples; ++sample)
            data[sample] = generator.getY(phasor.getNextPhase());
    }

    template <typename Generator>
    void process(Generator& generator, Buffer& buffer) noexcept
    {
        process(generator, buffer.getWritePointer(0), buffer.getNumSamples());
        Buffers::copyToAllChannels(buffer);
    }

private:
    Phasor phasor;
};
} // namespace EA::Audio