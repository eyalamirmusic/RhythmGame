#pragma once

#include <ea_audio_common/ea_audio_common.h>

namespace EA::Audio::Plugins::RhythmGame
{
struct Parameters
{
    void addTo(AudioProcessor& p)
    {
        addParameters(p, {oscillator, volume, cutoff, reso});
    }

    ChoiceParam* oscillator = new ChoiceParam(
        {"OSC", 1}, "OSC", {"Square", "Sine", "Saw", "Reversed Saw", "Noise"}, 0);
    FloatParam* volume = new FloatParam({"Volume", 1}, "Volume", 0.f, 0.5f, 0.25f);
    FloatParam* cutoff = new FloatParam({"Cutoff", 1}, "Cutoff", 100.f, 20000.f, 10000.f);
    FloatParam* reso = new FloatParam({"Reso", 1}, "Reso", 0.01f, 3.f, 1.f);
};
} // namespace EA::Audio::Plugins::RhythmGame
