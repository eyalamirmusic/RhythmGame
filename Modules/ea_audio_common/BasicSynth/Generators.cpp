#include "Generators.h"

namespace EA::Audio::Generators
{

float Saw::getY(float x) noexcept
{
    return juce::jmap(x, -1.f, 1.f);
}

float ReverseSaw::getY(float x) noexcept
{
    return juce::jmap(1.f - x, -1.f, 1.f);
}

float Sine::getY(float x) noexcept
{
    return std::sin(juce::MathConstants<float>::twoPi * x);
}

float Square::getY(float x) noexcept
{
    if (x > 0.5f)
        return 1.f;

    return 0.f;
}

float WhiteNoise::getY(float) noexcept
{
    return juce::jmap(random.nextFloat(), -1.f, 1.f);
}
} // namespace EA::Audio::Generators
