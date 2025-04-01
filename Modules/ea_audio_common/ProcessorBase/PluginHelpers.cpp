#include "PluginHelpers.h"

namespace EA::Audio::Plugins
{

void addParameters(AudioProcessor& p,
                   std::initializer_list<juce::AudioProcessorParameter*> params)
{
    for (auto& param: params)
        p.addParameter(param);
}
} // namespace EA::Audio::Plugins
