#pragma once

#include "../Common/Common.h"

namespace EA::Audio
{
struct Transport
{
    void prepare(double srToUse, int blockSize);
    void process(int numSamples) noexcept;
    void process(const juce::AudioPlayHead* ph, int numSamples) noexcept;

    int getNumSamples() const noexcept;

    bool playing = true;

    double bpm = 100.0;
    double pos = 0.0;
    double sr = 0.0;

    Vector<juce::Range<double>> positions;
};
} // namespace EA::Audio