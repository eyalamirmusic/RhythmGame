#pragma once

#include "VoiceBase.h"
#include "Oscillator.h"
#include "Generators.h"

namespace EA::Audio
{

struct WhiteNoise
{
    void processChannel(float* channelData, int numSamples) noexcept;
    void process(Buffer& buffer) noexcept;

    juce::Random random;
};

enum class BasicSynthOSCOptions
{
    Sine,
    Square,
    Saw,
    ReversedSaw,
    WhiteNoise
};

struct OscillatorList
{
    Generators::WhiteNoise noise;
    Generators::Sine sine;
    Generators::Square square;
    Generators::Saw saw;
    Generators::ReverseSaw reversedSaw;

    BasicSynthOSCOptions selected = BasicSynthOSCOptions::Sine;
};

struct BasicSynthShared
{
    BasicSynthShared()
    {
        adsr.attack = 0.0001f;
        adsr.decay = 100.f;
        adsr.sustain = 1.f;
        adsr.release = 0.001f;
    }

    juce::ADSR::Parameters adsr;
    OscillatorList oscs;
};

struct BasicSynthVoice : VoiceBase
{
    void noteStarted() override;
    void noteStopped(bool allowTailOff) override;
    void process(Buffer& buffer) noexcept override;
    void prepare(double sr, int);

    BasicSynthShared* shared = nullptr;

    juce::ADSR adsr;
    Oscillator osc;
};

using BasicSynth = MPESynth<BasicSynthVoice>;

} // namespace EA::Audio