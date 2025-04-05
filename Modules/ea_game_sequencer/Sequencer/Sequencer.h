#pragma once

#include <ea_audio_common/ea_audio_common.h>

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

struct TimedNote
{
    Note* operator->() { return &note; }
    const Note* operator->() const { return &note; }

    std::atomic<bool> playing {false};
    Note note;
    TimeRange time;
};

struct Sequence
{
    Sequence() = default;
    Sequence(const MidiMessageSequence& seq, double timeFormat, double timeToUse);

    juce::Range<int> getNoteRange() const;

    double time = 0.0;
    std::atomic<double> pos = 0.0;
    Vector<std::shared_ptr<TimedNote>> notes;
};

struct Player
{
    Player(const File& file);

    void process(MidiBuffer& midi, const Audio::Transport& transport) noexcept;

    double sequenceTime = 0.0;
    OwnedVector<Sequence> sequences;
    Vector<std::shared_ptr<TimedNote>> playingNotes;
    Vector<std::shared_ptr<TimedNote>> possibleNotes;
};
} // namespace EA::Sequencer