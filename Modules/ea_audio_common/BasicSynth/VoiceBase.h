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

template <typename T>
struct MPESynth : juce::MPESynthesiser
{
    MPESynth(int numVoices = 8) { addVoices(numVoices); }

    void addVoices(int numVoices)
    {
        for (int index = 0; index < numVoices; ++index)
        {
            auto newVoice = new T();
            newVoice->voiceBuffer = &voiceBuffer;
            synthVoices.emplace_back(newVoice);
            addVoice(newVoice);
        }
    }

    void process(Buffer& buffer, const MidiBuffer& midi) noexcept
    {
        renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
    }

    void prepare(int numChannels, double sr, int blockSize)
    {
        voiceBuffer.setSize(numChannels, blockSize);
        setCurrentPlaybackSampleRate(sr);

        for (auto& voice: synthVoices)
            voice->prepare(sr, blockSize);
    }

    Buffer voiceBuffer;
    std::vector<T*> synthVoices;
};
} // namespace EA::Audio
