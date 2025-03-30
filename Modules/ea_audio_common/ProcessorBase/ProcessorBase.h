#pragma once

#include "../Common/Common.h"

namespace EA::Audio
{
//A helper base class, reducing a lot of the AudioProcessor boiler plate:

struct ProcessorBase : AudioProcessor
{
    ProcessorBase();
    explicit ProcessorBase(const BusesProperties& ioLayouts);

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(Buffer& buffer, MidiBuffer& midiMessages) override;

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    static BusesProperties getDefaultProperties();
};
}

