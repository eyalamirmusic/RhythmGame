#include "Sequencer.h"

namespace EA::Sequencer
{
static double getTime(const MidiMessage& message, double timeFormat)
{
    return message.getTimeStamp() / timeFormat;
}

Note::Note(const MidiMessage& message) noexcept
{
    channel = message.getChannel();
    noteNum = message.getNoteNumber();
    velocity = message.getFloatVelocity();
}

MidiMessage Note::toNoteOn() const noexcept
{
    return MidiMessage::noteOn(channel, noteNum, velocity);
}

MidiMessage Note::toNoteOff() const noexcept
{
    return MidiMessage::noteOff(channel, noteNum, velocity);
}

Sequence::Sequence(const MidiMessageSequence& seq, double timeFormat, double timeToUse)
    : duration(timeToUse)
{
    for (auto& midiNote: seq)
    {
        auto& m = midiNote->message;

        if (m.isNoteOn())
        {
            auto start = getTime(m, timeFormat);
            auto end = getTime(midiNote->noteOffObject->message, timeFormat);

            auto note = std::make_shared<TimedNote>();
            note->time.start = start;
            note->time.length = end - start;

            note->note = Note(m);
            notes.push_back(note);
        }
    }
}
juce::Range<int> Sequence::getNoteRange() const
{
    if (notes.empty())
        return {};

    int lowest = notes[0]->note.noteNum;
    int highest = notes[0]->note.noteNum;

    for (auto& note: notes)
    {
        auto noteNum = note->note.noteNum;

        if (noteNum < lowest)
            lowest = noteNum;

        if (noteNum > highest)
            highest = noteNum;
    }

    return {lowest, highest};
}

MultiSequence::MultiSequence(const File& file)
{
    auto midiFile = juce::MidiFile();

    if (auto stream = file.createInputStream())
    {
        midiFile.readFrom(*stream);
        sequenceTime = midiFile.getLastTimestamp() / midiFile.getTimeFormat();

        for (int track = 0; track < midiFile.getNumTracks(); ++track)
        {
            auto sequence = makeOwned<Sequence>(
                *midiFile.getTrack(track), midiFile.getTimeFormat(), sequenceTime);

            if (!sequence->notes.empty())
                sequences.add(std::move(sequence));
        }
    }
}

Player::Player()
{
    playingNotes.reserve(1000);
    possibleNotes.reserve(1000);
}

void Player::process(Sequence& seq,
                     MidiBuffer& midi,
                     const Audio::Transport& transport) noexcept
{
    if (!transport.playing)
    {
        for (auto& note: playingNotes)
            midi.addEvent(note->note.toNoteOff(), 0);

        playingNotes.clear();

        return;
    }

    auto fullRange = transport.getRange();

    possibleNotes.clear();

    for (auto& note: seq.notes)
    {
        if (note->time.intersects(fullRange))
            possibleNotes.add(note);
    }

    for (int sample = 0; sample < transport.getNumSamples(); ++sample)
    {
        auto pos = transport.positions[sample];

        for (int index = playingNotes.getLastElementIndex(); index >= 0; --index)
        {
            auto& note = playingNotes[index];

            if (!note->time.intersects(pos))
            {
                midi.addEvent(note->note.toNoteOff(), 0);
                note->playing.store(false);
                playingNotes.removeAt(index);
            }
        }

        for (auto& note: possibleNotes)
        {
            if (!note->playing.load() && pos.intersects(note->time))
            {
                note->playing.store(true);
                playingNotes.add(note);
                midi.addEvent(note->note.toNoteOn(), sample);
            }
        }
    }

    seq.pos.store(fullRange.getEnd() / seq.duration);
}
} // namespace EA::Sequencer