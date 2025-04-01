#pragma once

#include "Transport.h"

namespace EA::MIDI
{
using juce::MidiBuffer;
using juce::MidiMessage;
using juce::MidiMessageSequence;

struct Note
{
    Note() = default;
    Note(const MidiMessage& message)
    {
        channel = message.getChannel();
        noteNum = message.getNoteNumber();
        velocity = message.getFloatVelocity();
    }

    MidiMessage toNoteOn() const
    {
        return MidiMessage::noteOn(channel, noteNum, velocity);
    }

    MidiMessage toNoteOff() const
    {
        return MidiMessage::noteOff(channel, noteNum, velocity);
    }

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

inline double getTime(const MidiMessage& message, double timeFormat)
{
    return message.getTimeStamp() / timeFormat;
}

struct Sequence
{
    Sequence() = default;
    Sequence(const MidiMessageSequence& seq, double timeFormat)
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

    Vector<TimedNote> notes;
};

struct Player
{
    Player(const File& file)
    {
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

    void process(MidiBuffer& midi, const Audio::Transport& transport)
    {
        for (int sample = 0; sample < transport.getNumSamples(); ++sample)
        {
            auto pos = transport.positions[sample];

            for (auto& sequence: sequences)
            {
                for (auto& note: sequence.notes)
                {
                    auto& time = note.time;

                    if (pos.contains(time.start))
                        midi.addEvent(note.note.toNoteOn(), sample);
                    else if (pos.contains(time.getEnd()))
                        midi.addEvent(note.note.toNoteOff(), sample);
                }
            }
        }
    }

    Vector<Sequence> sequences;
};
} // namespace EA::MIDI