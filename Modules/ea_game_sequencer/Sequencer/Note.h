#pragma once

#include "Common.h"

namespace EA::Sequencer
{
struct Note
{
    Note() = default;
    Note(int noteNumToUse, float velocityToUse = 0.8f, int channelToUse = 1);

    Note(const MidiMessage& message) noexcept;

    MidiMessage toNoteOn() const noexcept;
    MidiMessage toNoteOff() const noexcept;

    int noteNum = 0;
    float velocity = 0.8f;
    int channel = 1;
};

struct TimedNote
{
    TimedNote() = default;
    TimedNote(const Note& noteToUse, const TimeRange& timeToUse);

    Note* operator->() { return &note; }
    const Note* operator->() const { return &note; }

    CopyableAtomic<bool> playing {false};
    Note note;
    TimeRange time {};
};

using SharedNote = std::shared_ptr<TimedNote>;
} // namespace EA::Sequencer