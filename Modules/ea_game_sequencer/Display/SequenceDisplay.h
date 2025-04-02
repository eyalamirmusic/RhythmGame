#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../Sequencer/Sequencer.h"

namespace EA::GUI
{
using juce::Colour;
using juce::Component;
using juce::Graphics;
using juce::Path;
using juce::Point;
using juce::Rectangle;
namespace Colours = juce::Colours;

struct Playhead : Component
{
    void paint(Graphics& g) override { g.fillAll(Colours::white); }
};

struct SequenceDisplay : Component
{
    SequenceDisplay(Sequencer::Sequence& seqToUse)
        : seq(seqToUse)
    {
        addAndMakeVisible(ph);
    }

    void update()
    {
        auto x = (float) seq.pos.load();
        ph.setBoundsRelative(x, 0.f, 0.01f, 1.f);
    }

    Sequencer::Sequence& seq;
    Playhead ph;
    Events::Timer timer {[&] { update(); }};
};
} // namespace EA::GUI