#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <ea_common/ea_common.h>

namespace EA::Audio
{
using Buffer = juce::AudioBuffer<float>;
using juce::AudioProcessor;
using juce::AudioProcessorEditor;
using juce::MidiBuffer;

using FloatParam = juce::AudioParameterFloat;
using ChoiceParam = juce::AudioParameterChoice;
using BoolParam = juce::AudioParameterBool;
using IntParam = juce::AudioParameterInt;

} // namespace EA::Audio
