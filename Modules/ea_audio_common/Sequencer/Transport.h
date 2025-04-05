#pragma once

#include "../Common/Common.h"

namespace EA::Audio
{
struct Transport
{
    using Range = juce::Range<double>;

    void prepare(double srToUse, int blockSize);
    void process(int numSamples) noexcept;
    void process(const juce::AudioPlayHead* ph, int numSamples) noexcept;

    Range getRange() const noexcept;

    int getNumSamples() const noexcept;

    bool playing = true;

    double bpm = 100.0;
    double pos = 0.0;
    double sr = 0.0;

    Vector<Range> positions;
};
} // namespace EA::Audio