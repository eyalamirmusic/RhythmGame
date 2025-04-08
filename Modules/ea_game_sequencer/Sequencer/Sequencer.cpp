#include "Sequencer.h"

namespace EA::Sequencer
{
static double getTime(const MidiMessage& message, double timeFormat)
{
    return message.getTimeStamp() / timeFormat;
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

    seq.pos.store(fullRange.getEnd());
}

MultiPlayer::MultiPlayer(int maxPlayers)
{
    players.resize(maxPlayers);
}

void MultiPlayer::process(MultiSequence& seq,
                          MidiBuffer& midi,
                          const Audio::Transport& transport)
{
    for (int index = 0; index < seq.sequences.size(); ++index)
        players[index].process(*seq.sequences[index], midi, transport);
}
} // namespace EA::Sequencer