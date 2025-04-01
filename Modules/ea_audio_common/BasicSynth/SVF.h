#pragma once

#include "../Common/Common.h"
#include <juce_dsp/juce_dsp.h>

namespace EA::Audio::Filters
{
class SVF
{
    using Filter = juce::dsp::StateVariableTPTFilter<float>;

public:
    void reset() { filter.reset(); }

    void prepare(int numChannels, double sr, int block);

    void process(Buffer& buffer,
                 float freq,
                 float resonance,
                 Filter::Type type = Filter::Type::lowpass) noexcept;

private:
    Filter filter;
};
} // namespace EA::Audio::Filters