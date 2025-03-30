#include "VoiceBase.h"
#include "../Buffers/Buffers.h"

namespace EA::Audio
{

void VoiceBase::renderNextBlock(Buffer& outputBuffer, int startSample, int numSamples)
{
    auto targetBuf = Buffers::getSub(outputBuffer, startSample, numSamples);
    auto sub = Buffers::getSub(*voiceBuffer, 0, numSamples);
    sub.clear();
    process(sub);
    Buffers::mix(sub, targetBuf);
}
} // namespace EA::Audio
