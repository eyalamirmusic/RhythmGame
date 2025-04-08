#pragma once

#include "Sequence.h"

namespace EA::Sequencer
{
static TimeRange getPlayRange(const TimedNote& note)
{
    auto range = note.time;
    range.start-= 0.125;
    range.length = 0.25;

    return range;
}

struct UserScore
{
    void userNote(Sequence& seq)
    {
        userActionPos = seq.pos.load();

        bool success = false;

        for (auto& note: seq.notes)
        {
            if (note->playing.load() && !playedNotes.contains(note))
            {
                auto range = getPlayRange(*note);

                if (range.contains(userActionPos))
                {
                    playedNotes.add(note);
                    success = true;
                }

            }
        }

        if (success)
            ++score;
        else
            --score;
    }

    Vector<SharedNote> playedNotes;

    int score = 0;
    double userActionPos = 0.0;
};

struct GameState
{
    Sequence& getActiveSequence() { return *multiSeq.sequences[activeSequence]; }
    void userNote() { score.userNote(getActiveSequence()); }

    int activeSequence = 0;

    MultiSequence multiSeq;
    UserScore score;
};
} // namespace EA::Sequencer