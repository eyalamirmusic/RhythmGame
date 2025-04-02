#include "Timer.h"

namespace EA::Events
{

Timer::Timer(const CallbackFunc& cbToUse, int hz)
    : cb(cbToUse)
{
    startTimerHz(hz);
}

Timer::~Timer()
{
    stopTimer();
}
void Timer::timerCallback()
{
    cb();
}
} // namespace EA::Events