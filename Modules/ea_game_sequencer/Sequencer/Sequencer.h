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
    Note(int noteNumToUse, float velocityToUse = 0.8f, int channelToUse = 1)
        : noteNum(noteNumToUse)
        , velocity(velocityToUse)
        , channel(channelToUse)
    {
    }

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
    TimedNote(const Note& noteToUse, const TimeRange& timeToUse)
        : note(noteToUse)
        , time(timeToUse)
    {
    }

    Note* operator->() { return &note; }
    const Note* operator->() const { return &note; }

    CopyableAtomic<bool> playing {false};
    Note note;
    TimeRange time {};
};

using SharedNote = std::shared_ptr<TimedNote>;

struct Sequence
{
    Sequence() = default;
    Sequence(const MidiMessageSequence& seq, double timeFormat, double timeToUse);

    juce::Range<int> getNoteRange() const;

    TimedNote& create(const TimedNote& newNote = {})
    {
        return *notes.create(std::make_shared<TimedNote>(newNote));
    }

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

struct Player
{
    Player();

    void process(Sequence& sequence,
                 MidiBuffer& midi,
                 const Audio::Transport& transport) noexcept;

    Vector<SharedNote> playingNotes;
    Vector<SharedNote> possibleNotes;
};

struct MultiPlayer
{
    MultiPlayer(int maxPlayers = 16) { players.resize(maxPlayers); }

    void process(MultiSequence& seq, MidiBuffer& midi, const Audio::Transport& transport)
    {
        for (int index = 0; index < seq.sequences.size(); ++index)
            players[index].process(*seq.sequences[index], midi, transport);
    }

    Vector<Player> players;
};

} // namespace EA::Sequencer