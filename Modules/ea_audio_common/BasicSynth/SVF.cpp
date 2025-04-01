#include "SVF.h"

namespace EA::Audio::Filters
{
void SVF::prepare(int numChannels, double sr, int block)
{
    auto spec = juce::dsp::ProcessSpec();
    spec.numChannels = (uint32_t) numChannels;
    spec.sampleRate = sr;
    spec.maximumBlockSize = (uint32_t) block;

    filter.prepare(spec);
}

void SVF::process(Buffer& buffer, float freq, float resonance, Filter::Type type) noexcept
{
    filter.setCutoffFrequency(freq);
    filter.setResonance(resonance);
    filter.setType(type);

    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing(block);
    filter.process(context);
}
} // namespace EA::Audio::Filters
