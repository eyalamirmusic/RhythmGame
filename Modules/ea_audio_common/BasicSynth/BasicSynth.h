#pragma once

#include "../Buffers/Buffers.h"

namespace EA::Audio
{

struct VoiceBase : juce::MPESynthesiserVoice
{
    void notePressureChanged() override {}
    void notePitchbendChanged() override {}
    void noteTimbreChanged() override {}
    void noteKeyStateChanged() override {}

    virtual void process(Buffer& buffer) noexcept = 0;

    void renderNextBlock(Buffer& outputBuffer, int startSample, int numSamples) override
    {
        auto sub = Buffers::getSub(outputBuffer, startSample, numSamples);
        process(sub);
    }
};

struct BasicSynthVoice : VoiceBase
{
    void noteStarted() override { adsr.noteOn(); }
    void noteStopped(bool allowTailOff) override
    {
        adsr.noteOff();

        if (!allowTailOff)
            clearCurrentNote();
    }

    void process(Buffer& buffer) noexcept override
    {
        auto channelData = buffer.getWritePointer(0);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto next = random.nextFloat();
            channelData[sample] = juce::jmap(next, -1.f, 1.f);
        }

        Buffers::copyToAllChannels(buffer);
        buffer.applyGain(0.3f);

        adsr.applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());

        if (!adsr.isActive())
            clearCurrentNote();
    }

    void prepare(double sr, int) { adsr.setSampleRate(sr); }

    juce::Random random;
    juce::ADSR adsr;
};

struct BasicSynth : juce::MPESynthesiser
{
    BasicSynth()
    {
        for (int index = 0; index < 4; ++index)
        {
            auto newVoice = new BasicSynthVoice();
            synthVoices.emplace_back(newVoice);
            addVoice(newVoice);
        }
    }

    void prepare(double sr, int blockSize)
    {
        setCurrentPlaybackSampleRate(sr);

        for (auto& voice: synthVoices)
            voice->prepare(sr, blockSize);
    }

    void process(Buffer& buffer, const MidiBuffer& midi) noexcept
    {
        renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
    }

    std::vector<BasicSynthVoice*> synthVoices;
};
} // namespace EA::Audio