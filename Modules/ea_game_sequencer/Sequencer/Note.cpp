#include "Note.h"

namespace EA::Sequencer
{
Note::Note(int noteNumToUse, float velocityToUse, int channelToUse)
    : noteNum(noteNumToUse)
    , velocity(velocityToUse)
    , channel(channelToUse)
{
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

TimedNote::TimedNote(const Note& noteToUse, const TimeRange& timeToUse)
    : note(noteToUse)
    , time(timeToUse)
{
}

} // namespace EA::Sequencer