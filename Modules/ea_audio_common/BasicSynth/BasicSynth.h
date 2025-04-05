#pragma once

#include "VoiceBase.h"
#include "Oscillator.h"
#include "Generators.h"
#include "SVF.h"
#include "../Buffers/SmoothGain.h"

namespace EA::Audio::BasicSynth
{

enum class OSCOptions
{
    Square,
    Sine,
    Saw,
    ReversedSaw,
    WhiteNoise
};

struct OscillatorList
{
    Generators::WhiteNoise noise;
    Generators::Table<Generators::Sine> sine;
    Generators::Table<Generators::Square> square;
    Generators::Table<Generators::Saw> saw;
    Generators::Table<Generators::ReverseSaw> reversedSaw;

    OSCOptions selected = OSCOptions::Square;
};

struct FilterParams
{
    float cutoff = 8000.f;
    float reso = 1.f;
};

struct BasicSynthShared
{
    BasicSynthShared();

    juce::ADSR::Parameters adsr;
    OscillatorList oscs;
    FilterParams filter;
};

struct Voice : VoiceBase
{
    void noteStarted() override;
    void noteStopped(bool allowTailOff) override;
    void process(Buffer& buffer) noexcept override;
    void prepare(int numChannels, double sr, int block);

    BasicSynthShared* shared = nullptr;

    float gain = 0.f;

    Filters::SVF filter;
    juce::ADSR adsr;
    Oscillator osc;
};

struct Synth : MPESynth<Voice>
{
    Synth();

    BasicSynthShared shared;
};

} // namespace EA::Audio::BasicSynth