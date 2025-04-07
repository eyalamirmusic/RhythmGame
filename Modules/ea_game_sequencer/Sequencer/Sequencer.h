#pragma once

#include "Sequence.h"

namespace EA::Sequencer
{
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
    MultiPlayer(int maxPlayers = 16);

    void process(MultiSequence& seq, MidiBuffer& midi, const Audio::Transport& transport);

    Vector<Player> players;
};

} // namespace EA::Sequencer