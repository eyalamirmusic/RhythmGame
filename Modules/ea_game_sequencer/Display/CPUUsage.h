#pragma once

#include <ea_gui_common/ea_gui_common.h>
#include <ea_audio_common/ea_audio_common.h>

namespace EA::GUI
{
struct CPUUsage : Component
{
    CPUUsage(juce::AudioProcessLoadMeasurer& measurerToUse)
        : measurer(measurerToUse)
    {
        setSize(400, 400);
    }

    void paint(Graphics& g) override
    {
        g.setColour(Colours::white);
        auto text = String(measurer.getLoadAsPercentage()) + "%";
        g.drawFittedText(text, getLocalBounds(), juce::Justification::centred, 1);
    }

    juce::AudioProcessLoadMeasurer& measurer;
    Events::Timer timer {[&] { repaint(); }};
};
} // namespace EA::GUI