#pragma once

namespace EA::Audio::Generators
{
struct Saw
{
    static float getY(float x) noexcept;
};

struct ReverseSaw
{
    static float getY(float x) noexcept;
};

struct Sine
{
    static float getY(float x) noexcept;
};

struct Square
{
    static float getY(float x) noexcept;
};

struct WhiteNoise
{
    float getY(float) noexcept;

    juce::Random random;
};
} // namespace EA::Audio::Generators
