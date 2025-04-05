#pragma once

namespace EA
{
struct TimeRange
{
    TimeRange() = default;
    TimeRange(double startToUse, double lengthToUse);

    static TimeRange withStartEnd(double startToUse, double endToUse) noexcept;

    bool intersects(const TimeRange& other) const noexcept;
    bool contains(double pos) const noexcept;
    double getEnd() const noexcept;

    double start = 0.0;
    double length = 0.0;
};

} // namespace EA