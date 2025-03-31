#include <ea_audio_common/ea_audio_common.h>

int main()
{
    auto file = EA::Files::getDesktop() / "MIDI" / "bwv772.mid";
    auto player = EA::MIDI::Player(file);

    return 0;
}
