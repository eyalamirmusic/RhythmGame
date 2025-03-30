#pragma once

#include "VoiceBase.h"

namespace EA::Audio
{

struct WhiteNoise
{
    void processChannel(float* channelData, int numSamples) noexcept;
    void process(Buffer& buffer) noexcept;

    juce::Random random;
};

struct BasicSynthVoice : VoiceBase
{
    void noteStarted() override;
    void noteStopped(bool allowTailOff) override;
    void process(Buffer& buffer) noexcept override;
    void prepare(double sr, int);

    juce::ADSR adsr;
    WhiteNoise whiteNoise;
};

using BasicSynth = MPESynth<BasicSynthVoice>;

} // namespace EA::Audio