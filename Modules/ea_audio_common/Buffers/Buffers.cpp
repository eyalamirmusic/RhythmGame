#include "Buffers.h"

namespace EA::Audio::Buffers
{
using FVO = juce::FloatVectorOperations;

Buffer getSub(Buffer& source, int startSample, int length) noexcept
{
    return {
        source.getArrayOfWritePointers(), source.getNumChannels(), startSample, length};
}

template <typename Func>
void processAllChannels(const Buffer& source, Buffer& target, Func&& func) noexcept
{
    auto numChannels = std::min(source.getNumChannels(), target.getNumChannels());
    auto numSamples = std::min(source.getNumSamples(), target.getNumSamples());

    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto sourceData = source.getReadPointer(channel);
        auto targetData = target.getWritePointer(channel);

        func(sourceData, targetData, numSamples);
    }
}

void copy(const Buffer& source, Buffer& target) noexcept
{
    auto func = [](const float* sourceData, float* targetData, int numSamples)
    { FVO::copy(targetData, sourceData, numSamples); };

    processAllChannels(source, target, func);
}

void mix(const Buffer& source, Buffer& target) noexcept
{
    auto func = [](const float* sourceData, float* targetData, int numSamples)
    { FVO::add(targetData, sourceData, numSamples); };

    processAllChannels(source, target, func);
}

void mixGain(const Buffer& source, Buffer& target, float gain) noexcept
{
    auto func = [gain](const float* sourceData, float* targetData, int numSamples)
    { FVO::addWithMultiply(targetData, sourceData, gain, numSamples); };

    processAllChannels(source, target, func);
}

void copyToAllChannels(Buffer& buffer, int sourceChannel) noexcept
{
    auto sourceData = buffer.getReadPointer(sourceChannel);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        if (channel != sourceChannel)
        {
            auto target = buffer.getWritePointer(channel);
            FVO::copy(target, sourceData, buffer.getNumSamples());
        }
    }
}
void clip(Buffer& buffer, float level) noexcept
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto target = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            target[sample] = juce::jlimit(-level, level, target[sample]);
    }
}
} // namespace EA::Audio::Buffers
