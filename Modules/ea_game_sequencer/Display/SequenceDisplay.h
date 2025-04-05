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
        repaint();
    }

    void paint(Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        for (auto& note: seq.notes)
        {
            auto& time = note.time;

            auto x = float(time.start / seq.time);
            auto w = float(time.length / seq.time);
            auto y = (float)note->noteNum / 128.f;
            auto h = 1.f / 128.f;

            auto scaledRect = Scaling::scaleRect(bounds, {x, y, w, h});

            g.setColour(Colours::blue);
            g.fillRect(scaledRect);

            g.setColour(Colours::white);
            g.drawRect(scaledRect);
        }
    }

    Sequencer::Sequence& seq;
    Playhead ph;
    Events::Timer timer {[&] { update(); }};
};
} // namespace EA::GUI