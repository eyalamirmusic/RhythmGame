#pragma once

#include "../Common/Common.h"

namespace EA::Audio
{

constexpr double getSamplesPerBeat(double sampleRate, double tempo) noexcept
{
    auto samplesInMinute = sampleRate * 60.0;

    return samplesInMinute / tempo;
}

constexpr double getPPQPerSample(double sampleRate, double tempo) noexcept
{
    return 1.0 / getSamplesPerBeat(sampleRate, tempo);
}

struct Transport
{
    void prepare(double srToUse, int blockSize)
    {
        sr = srToUse;
        positions.reserve(blockSize);
    }

    void process(int numSamples) noexcept
    {
        positions.resize(numSamples);

        auto offset = getPPQPerSample(sr, bpm);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            auto end = pos + offset;
            positions[sample] = {pos, end};
            pos = end;
        }
    }

    void process(const juce::AudioPlayHead* ph, int numSamples) noexcept
    {
        if (ph != nullptr)
        {
            if (auto hostPos = ph->getPosition())
            {
                if (auto tempo = hostPos->getBpm())
                    bpm = *tempo;

                if (auto ppq = hostPos->getPpqPosition())
                    pos = *ppq;

                playing = hostPos->getIsPlaying();
            }
        }

        process(numSamples);
    }

    int getNumSamples() const noexcept { return positions.size(); }

    bool playing = true;

    double bpm = 100.0;
    double pos = 0.0;
    double sr = 0.0;
    Vector<juce::Range<double>> positions;
};
} // namespace EA::Audio