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

struct BasicSynth : juce::MPESynthesiser
{
    BasicSynth();

    void prepare(int numChannels, double sr, int blockSize);
    void process(Buffer& buffer, const MidiBuffer& midi) noexcept;

    Buffer voiceBuffer;
    std::vector<BasicSynthVoice*> synthVoices;
};
} // namespace EA::Audio