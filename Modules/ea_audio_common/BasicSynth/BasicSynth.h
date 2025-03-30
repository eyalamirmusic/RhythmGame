#pragma once

#include "VoiceBase.h"

namespace EA::Audio
{

struct BasicSynthVoice : VoiceBase
{
    void noteStarted() override;
    void noteStopped(bool allowTailOff) override;
    void process(Buffer& buffer) noexcept override;
    void prepare(double sr, int);

    juce::Random random;
    juce::ADSR adsr;
};

using BasicSynth = MPESynth<BasicSynthVoice>;

} // namespace EA::Audio