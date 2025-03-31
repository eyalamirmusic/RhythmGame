#pragma once

#include "VoiceBase.h"
#include "Oscillator.h"
#include "Generators.h"

namespace EA::Audio::BasicSynth
{

enum class OSCOptions
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

    OSCOptions selected = OSCOptions::Sine;
};

struct BasicSynthShared
{
    BasicSynthShared();

    juce::ADSR::Parameters adsr;
    OscillatorList oscs;
};

struct Voice : VoiceBase
{
    void noteStarted() override;
    void noteStopped(bool allowTailOff) override;
    void process(Buffer& buffer) noexcept override;
    void prepare(double sr, int);

    BasicSynthShared* shared = nullptr;

    juce::ADSR adsr;
    Oscillator osc;
};

struct Synth : MPESynth<Voice>
{
    Synth();

    BasicSynthShared shared;
};

} // namespace EA::Audio