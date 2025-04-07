#pragma once



namespace EA::Sequencer
{

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
                playedNotes.add(note);
                success = true;
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
}