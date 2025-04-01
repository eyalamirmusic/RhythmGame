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

Sequence::Sequence(const MidiMessageSequence& seq, double timeFormat)
{
    for (auto& midiNote: seq)
    {
        auto& m = midiNote->message;

        if (m.isNoteOn())
        {
            auto start = getTime(m, timeFormat);
            auto end = getTime(midiNote->noteOffObject->message, timeFormat);

            auto note = TimedNote();
            note.time.start = start;
            note.time.length = end - start;

            note.note = Note(m);
            notes.push_back(note);
        }
    }
}

Player::Player(const File& file)
{
    playingNotes.reserve(100);

    auto midiFile = juce::MidiFile();

    if (auto stream = file.createInputStream())
        midiFile.readFrom(*stream);

    for (int track = 0; track < midiFile.getNumTracks(); ++track)
    {
        auto sequence = Sequence(*midiFile.getTrack(track), midiFile.getTimeFormat());

        if (!sequence.notes.empty())
            sequences.add(sequence);
    }
}
void Player::process(MidiBuffer& midi, const Audio::Transport& transport)
{
    if (!transport.playing)
    {
        for (auto& note: playingNotes)
            midi.addEvent(note.note.toNoteOff(), 0);

        playingNotes.clear();

        return;
        ;
    }

    for (int sample = 0; sample < transport.getNumSamples(); ++sample)
    {
        auto pos = transport.positions[sample];

        for (int index = playingNotes.getLastElementIndex(); index >= 0; --index)
        {
            auto& note = playingNotes[index];

            if (!note.time.intersects(pos))
            {
                midi.addEvent(note.note.toNoteOff(), 0);
                playingNotes.removeAt(index);
            }
        }

        for (auto& sequence: sequences)
        {
            for (auto& note: sequence.notes)
            {
                auto& time = note.time;

                if (pos.contains(time.start))
                {
                    playingNotes.add(note);
                    midi.addEvent(note.note.toNoteOn(), sample);
                }
            }
        }
    }
}
} // namespace EA::Sequencer