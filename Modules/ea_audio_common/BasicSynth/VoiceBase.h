#pragma once

#include "../Common/Common.h"

namespace EA::Audio
{
struct VoiceBase : juce::MPESynthesiserVoice
{
    void notePressureChanged() override {}
    void notePitchbendChanged() override {}
    void noteTimbreChanged() override {}
    void noteKeyStateChanged() override {}

    virtual void process(Buffer& buffer) noexcept = 0;

    void renderNextBlock(Buffer& outputBuffer, int startSample, int numSamples) override;

    Buffer* voiceBuffer = nullptr;
};
}
