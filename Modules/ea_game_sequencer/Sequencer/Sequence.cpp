#include "Sequence.h"

namespace EA::Sequencer
{

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

TimedNote& Sequence::create(const TimedNote& newNote)
{
    return *notes.create(std::make_shared<TimedNote>(newNote));
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

} // namespace EA::Sequencer