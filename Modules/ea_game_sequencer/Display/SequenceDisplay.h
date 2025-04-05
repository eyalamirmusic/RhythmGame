#pragma once

#include <ea_gui_common/ea_gui_common.h>
#include "../Sequencer/Sequencer.h"

namespace EA::GUI
{
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
        Scaling::scale(ph, {x, 0.f, 0.01f, 1.f});
    }

    Sequencer::Sequence& seq;
    Playhead ph;
    Events::Timer timer {[&] { update(); }};
};
} // namespace EA::GUI