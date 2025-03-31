#include "ProcessorBase.h"

namespace EA::Audio
{
ProcessorBase::ProcessorBase()
    : AudioProcessor(getDefaultProperties())
{
}

ProcessorBase::ProcessorBase(const BusesProperties& ioLayouts)
    : AudioProcessor(ioLayouts)
{
}

const String ProcessorBase::getName() const
{
#if defined JucePlugin_Name
    return JucePlugin_Name;
#else
    return {};
#endif
}

bool ProcessorBase::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ProcessorBase::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ProcessorBase::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ProcessorBase::getTailLengthSeconds() const
{
    return 0.0;
}

int ProcessorBase::getNumPrograms()
{
    return 1;
}

int ProcessorBase::getCurrentProgram()
{
    return 0;
}

void ProcessorBase::setCurrentProgram(int index)
{
    ignoreUnused(index);
}

const String ProcessorBase::getProgramName(int index)
{
    ignoreUnused(index);
    return {};
}

void ProcessorBase::changeProgramName(int index, const juce::String& newName)
{
    ignoreUnused(index, newName);
}

void ProcessorBase::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    ignoreUnused(sampleRate, samplesPerBlock);
}

void ProcessorBase::releaseResources()
{
}

AudioProcessor::BusesProperties ProcessorBase::getDefaultProperties()
{
    return BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
        ;
}

AudioProcessorEditor* ProcessorBase::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

bool ProcessorBase::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (isMidiEffect())
        return true;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

// This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}

void ProcessorBase::processBlock(Buffer& buffer, MidiBuffer& midiMessages)
{
    ignoreUnused(buffer, midiMessages);
}

void ProcessorBase::getStateInformation(MemoryBlock& destData)
{
    ignoreUnused(destData);
}

void ProcessorBase::setStateInformation(const void* data, int sizeInBytes)
{
    ignoreUnused(data, sizeInBytes);
}

} // namespace EA::Audio
