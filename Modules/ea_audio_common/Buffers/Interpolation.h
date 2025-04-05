#pragma once

#include <algorithm>

namespace EA::Audio::Interpolation
{
namespace Linear
{
    template <typename T, typename BufferType, typename PosType>
    static constexpr T getInterpolatedSample(const BufferType& values,
                                             int size,
                                             PosType position) noexcept
    {
        // Scale position to buffer range [0, size - 1]
        const PosType scaledPos = position * (size - 1);

        // Get indices
        const int index0 = static_cast<int>(scaledPos);
        const int index1 = std::min(index0 + 1, size - 1);

        // Get interpolation factor
        const T fraction = static_cast<T>(scaledPos - index0);

        // Perform linear interpolation
        return static_cast<T>(values[index0] * (1 - fraction)
                              + values[index1] * fraction);
    }
} // namespace Linear
namespace CatmullRom
{
    template <typename T, typename BufferType, typename PosType>
    static constexpr T getInterpolatedSample(const BufferType& values,
                                             int size,
                                             PosType position) noexcept
    {
        // Map position to [0, size - 1]
        const PosType scaledPos = position * (size - 1);

        int idx1 = static_cast<int>(scaledPos);
        PosType frac = scaledPos - idx1;

        // Neighbor indices for Catmull-Rom (ensure indices are within bounds)
        int idx0 = std::clamp(idx1 - 1, 0, size - 1);
        int idx2 = std::clamp(idx1 + 1, 0, size - 1);
        int idx3 = std::clamp(idx1 + 2, 0, size - 1);

        const T P0 = static_cast<T>(values[idx0]);
        const T P1 = static_cast<T>(values[idx1]);
        const T P2 = static_cast<T>(values[idx2]);
        const T P3 = static_cast<T>(values[idx3]);

        // Catmull-Rom spline interpolation formula
        const T frac2 = frac * frac;
        const T frac3 = frac2 * frac;

        return static_cast<T>(0.5
                              * ((2 * P1) + (-P0 + P2) * frac
                                 + (2 * P0 - 5 * P1 + 4 * P2 - P3) * frac2
                                 + (-P0 + 3 * P1 - 3 * P2 + P3) * frac3));
    }
} // namespace CatmullRom

} // namespace EA::Audio::Interpolation