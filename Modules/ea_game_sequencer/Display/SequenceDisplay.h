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
    }

    static Colour getNoteColor(const Sequencer::TimedNote& note)
    {
        if (note.playing.load())
            return Colours::red;

        return Colours::blue;
    }

    void paint(Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        for (auto& note: seq.notes)
        {
            auto& time = note->time;

            auto x = float(time.start / seq.time);
            auto w = float(time.length / seq.time);

            auto range = seq.getNoteRange();
            auto rangeLength = (float) range.getLength();

            auto y = float(note->note.noteNum - range.getStart()) / rangeLength;
            auto h = 1.f / rangeLength;
            y = 1.f - y - h;

            auto scaledRect = Scaling::scaleRect(bounds, {x, y, w, h});

            g.setColour(getNoteColor(*note));
            g.fillRect(scaledRect);

            g.setColour(Colours::white);
            g.drawRect(scaledRect);
        }
    }

    Sequencer::Sequence& seq;
};

struct ScrollingSequence : Component
{
    ScrollingSequence(Sequencer::Sequence& seqToUse)
        : seq(seqToUse)
    {
        viewPort.setViewedComponent(&display, false);
        viewPort.setScrollBarsShown(false, false);
        addAndMakeVisible(viewPort);
    }

    void resized() override
    {
        auto numBars = int(std::ceil(seq.time / 4.0));
        display.setBounds(0, 0, getWidth() * numBars, getHeight());
        viewPort.setBounds(getLocalBounds());
    }

    void update()
    {
        auto pos = seq.pos.load();
        auto width = display.getBounds().getWidth();
        auto x = pos * (float) width;
        x -= (float)getWidth() / 2.f;

        viewPort.setViewPosition((int) x, 0);
    }

    Sequencer::Sequence& seq;
    SequenceDisplay display {seq};
    Viewport viewPort;

    Events::Timer timer {[&] { update(); }};
};

struct ScrollingSequences : Component
{
    ScrollingSequences(Sequencer::Player& playerToUse)
    {
        for (auto& sequence: playerToUse.sequences)
        {
            sequences.createNew(*sequence);
            addAndMakeVisible(sequences.back());
        }
    }

    void resized() override { Scaling::resizeVertically(*this); }

    OwnedVector<ScrollingSequence> sequences;
};
} // namespace EA::GUI