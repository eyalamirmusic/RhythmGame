#pragma once

#include "../Common/Common.h"

namespace EA::Audio::Plugins
{

void addParameters(AudioProcessor& p,
                   std::initializer_list<juce::AudioProcessorParameter*> params);

} // namespace EA::Audio::Plugins