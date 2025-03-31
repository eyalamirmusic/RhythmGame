#include <ea_audio_common/ea_audio_common.h>

int main()
{
    using namespace EA::Audio;

    auto osc = Oscillator();
    auto gen = Generators::Sine();

    osc.setPitch(4000.f, 44100.f);

    auto vec = std::vector<float>();
    vec.resize(1000, 0.f);

    osc.process(gen, vec.data(), vec.size());

    for (auto& sample: vec)
        DBG(sample);

    return 0;
}
