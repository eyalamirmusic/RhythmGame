#include "Transport.h"

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

void Transport::prepare(double srToUse, int blockSize)
{
    sr = srToUse;
    positions.reserve(blockSize);
}

void Transport::process(int numSamples) noexcept
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
void Transport::process(const juce::AudioPlayHead* ph, int numSamples) noexcept
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

Transport::Range Transport::getRange() const noexcept
{
    return {positions[0].getStart(), positions.back().getEnd()};
}

int Transport::getNumSamples() const noexcept
{
    return positions.size();
}
} // namespace EA::Audio