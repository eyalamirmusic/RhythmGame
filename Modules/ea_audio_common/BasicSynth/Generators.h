#pragma once

#include "../Buffers/Interpolation.h"

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

template <typename Generator, int Size = 4096>
struct Table
{
    Table()
    {
        Generator generator;
        auto step = 1.f / (float) Size;
        auto pos = 0.f;

        for (int index = 0; index < Size; ++index)
        {
            table[index] = generator.getY(pos);
            pos += step;
        }
    }

    float getY(float pos) noexcept
    {
        return Interpolation::Linear::getInterpolatedSample<float>(table, Size, pos);
    }

    Array<float, Size> table;
};
} // namespace EA::Audio::Generators
