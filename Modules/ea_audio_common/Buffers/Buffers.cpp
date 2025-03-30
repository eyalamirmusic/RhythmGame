#include "Buffers.h"

namespace EA::Audio::Buffers
{
using FVO = juce::FloatVectorOperations;

Buffer getSub(Buffer& source, int startSample, int length) noexcept
{
    return {
        source.getArrayOfWritePointers(), source.getNumChannels(), startSample, length};
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
} // namespace EA::Audio::Buffers
