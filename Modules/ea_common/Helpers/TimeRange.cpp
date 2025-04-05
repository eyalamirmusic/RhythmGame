#include "TimeRange.h"

namespace EA
{

TimeRange::TimeRange(double startToUse, double lengthToUse)
    : start(startToUse)
    , length(lengthToUse)
{
}

TimeRange TimeRange::withStartEnd(double startToUse, double endToUse) noexcept
{
    return {startToUse, endToUse - startToUse};
}

bool TimeRange::intersects(const TimeRange& other) const noexcept
{
    return other.start < getEnd() && start < other.getEnd();
}

bool TimeRange::contains(double pos) const noexcept
{
    return pos >= start && pos < getEnd();
}

double TimeRange::getEnd() const noexcept
{
    return start + length;
}
} // namespace EA
