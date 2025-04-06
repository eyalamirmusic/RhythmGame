#pragma once

#include <ea_gui_common/ea_gui_common.h>
#include "../Sequencer/Sequencer.h"

namespace EA::GUI
{
struct Playhead : Component
{
    void paint(Graphics& g) override { g.fillAll(Colours::white); }
};

struct StructDisplayInfo
{
    StructDisplayInfo() = default;
    StructDisplayInfo(Sequencer::TimedNote& noteToUse, const Sequencer::Sequence& seq)
        : note(&noteToUse)
    {
        auto& time = note->time;

        auto x = float(time.start / seq.duration);
        auto w = float(time.length / seq.duration);

        auto range = seq.getNoteRange();
        auto rangeLength = (float) range.getLength() + 1;

        auto y = float(note->note.noteNum - range.getStart()) / rangeLength;
        auto h = 1.f / rangeLength;
        y = 1.f - y - h;

        rect = {x, y, w, h};
    }

    void scaleTo(const Rectangle<float>& target)
    {
        scaledRect = Scaling::scaleRect(target, rect);
    }

    Sequencer::TimedNote* note = nullptr;
    Rectangle<float> rect;
    Rectangle<float> scaledRect;
};

struct UserNote : Component
{
    void paint(Graphics& g) override { g.fillAll(Colours::green); }
};

struct UserHitArea : Component
{
    UserHitArea(Sequencer::Sequence& seqToUse, Sequencer::UserScore& userScoreToUse)
        : seq(seqToUse)
        , userScore(userScoreToUse)
    {
        addAndMakeVisible(userNote);
    }

    void onTimer()
    {
        auto width = float(1.0 / seq.duration);
        auto relativeTime = float(userScore.userActionPos);
        Scaling::scale(userNote, {relativeTime, 0.f, width, 1.f});
    }

    Sequencer::Sequence& seq;
    Sequencer::UserScore& userScore;

    UserNote userNote;
    Events::Timer timer {[&] { onTimer(); }};
};

struct SequenceDisplay : Component
{
    SequenceDisplay(Sequencer::Sequence& seqToUse)
        : seq(seqToUse)
    {
        for (auto& note: seq.notes)
            notes.create(*note, seq);
    }

    static float getNoteAlpha(const Sequencer::TimedNote& note)
    {
        return juce::jmap(note->velocity, 0.3f, 1.f);
    }

    static Colour getNoteColor(const Sequencer::TimedNote& note)
    {
        if (note.playing.load())
            return Colours::red;

        return Colours::blue.withAlpha(getNoteAlpha(note));
    }

    void resized() override
    {
        for (auto& note: notes)
            note.scaleTo(getLocalBounds().toFloat());
    }

    void paint(Graphics& g) override
    {
        auto bounds = g.getClipBounds().toFloat();

        for (auto& note: notes)
        {
            if (note.scaledRect.intersects(bounds))
            {
                g.setColour(getNoteColor(*note.note));
                g.fillRect(note.scaledRect);

                g.setColour(Colours::white);
                g.drawRect(note.scaledRect);
            }
        }
    }

    Sequencer::Sequence& seq;
    Vector<StructDisplayInfo> notes;

    Events::Timer timer {[&] { repaint(); }};
};

struct ScrollableArea : Component
{
    ScrollableArea(Sequencer::Sequence& seqToUse, Sequencer::UserScore& scoreToUse)
        : display(seqToUse)
        , userHitArea(seqToUse, scoreToUse)
    {
        addAndMakeVisible(display);
        addAndMakeVisible(userHitArea);
    }

    void resized() override
    {
        Scaling::scale(userHitArea, {0.f, 0.f, 1.f, 0.2f});
        Scaling::scale(display, {0.f, 0.2f, 1.f, 0.8f});
    }

    SequenceDisplay display;
    UserHitArea userHitArea;
};

struct ScrollingSequence : Component
{
    ScrollingSequence(Sequencer::Sequence& seqToUse, Sequencer::UserScore& scoreToUse)
        : seq(seqToUse)
        , area(seqToUse, scoreToUse)
    {
        viewPort.setViewedComponent(&area, false);
        viewPort.setScrollBarsShown(false, false);
        addAndMakeVisible(viewPort);
    }

    void resized() override
    {
        viewPort.setScrollBarsShown(false, false);
        auto numBars = int(std::ceil(seq.duration / 4.0));
        area.setBounds(0, 0, getWidth() * numBars, getHeight());
        viewPort.setBounds(getLocalBounds());

        update();
    }

    void update()
    {
        auto pos = seq.pos.load();
        auto width = area.getBounds().getWidth();
        auto x = pos * (float) width;
        x -= (float) getWidth() / 2.f;

        viewPort.setViewPosition((int) x, 0);
    }

    Sequencer::Sequence& seq;
    ScrollableArea area;
    Viewport viewPort;

    Events::Timer timer {[&] { update(); }};
};

struct ScrollingSequences : Component
{
    ScrollingSequences(Sequencer::MultiSequence& playerToUse, Sequencer::UserScore& score)
    {
        setInterceptsMouseClicks(false, false);

        for (auto& seq: playerToUse.sequences)
        {
            sequences.createNew(*seq, score);
            addAndMakeVisible(sequences.back());
        }
    }

    void resized() override { Scaling::resizeVertically(*this); }

    OwnedVector<ScrollingSequence> sequences;
};

struct ScoreDisplay : Component
{
    ScoreDisplay(Sequencer::UserScore& scoreToUse)
        : score(scoreToUse)
    {
        text.setJustificationType(juce::Justification::centred);
        text.setFont(juce::FontOptions(20.f));
        addAndMakeVisible(text);
    }

    void resized() override { text.setBounds(getLocalBounds()); }

    void update() { text.setText(String(score.score), juce::dontSendNotification); }

    Sequencer::UserScore& score;
    juce::Label text;
    Events::Timer timer {[&] { update(); }};
};

struct KeyboardHandling : Component
{
    KeyboardHandling(Sequencer::Sequence& seqToUse, Sequencer::UserScore& scoreToUse)
        : seq(seqToUse)
        , score(scoreToUse)
    {
        setWantsKeyboardFocus(true);
    }

    void visibilityChanged() override
    {
        if (isShowing())
            grabKeyboardFocus();
    }

    bool keyPressed(const juce::KeyPress&) override
    {
        score.userNote(seq);
        return true;
    }

    Sequencer::Sequence& seq;
    Sequencer::UserScore& score;
};
} // namespace EA::GUI