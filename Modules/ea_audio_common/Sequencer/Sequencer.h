#pragma once

#include "Transport.h"

namespace EA::Sequencer
{
using juce::MidiBuffer;
using juce::MidiMessage;
using juce::MidiMessageSequence;

struct Note
{
    Note() = default;
    Note(const MidiMessage& message) noexcept;

    MidiMessage toNoteOn() const noexcept;
    MidiMessage toNoteOff() const noexcept;

    int channel = 0;
    int noteNum = 0;
    float velocity = 0.f;
};

struct TimeRange
{
    double getEnd() const noexcept { return start + length; }

    double start = 0.0;
    double length = 0.0;
};

struct TimedNote
{
    Note note;
    TimeRange time;
};

struct Sequence
{
    Sequence() = default;
    Sequence(const MidiMessageSequence& seq, double timeFormat);

    Vector<TimedNote> notes;
};

struct Player
{
    Player(const File& file);

    void process(MidiBuffer& midi, const Audio::Transport& transport);

    Vector<Sequence> sequences;
};
} // namespace EA::MIDI