#pragma once

#include "Note.h"

namespace EA::Sequencer
{
struct Sequence
{
    Sequence() = default;
    Sequence(const MidiMessageSequence& seq, double timeFormat, double timeToUse);

    juce::Range<int> getNoteRange() const;

    TimedNote& create(const TimedNote& newNote = {});

    double duration = 0.0;
    std::atomic<double> pos = 0.0;
    Vector<SharedNote> notes;
};

struct MultiSequence
{
    MultiSequence() = default;

    MultiSequence(const File& file);

    double sequenceTime = 0.0;
    OwnedVector<Sequence> sequences;
};

} // namespace EA::Sequencer