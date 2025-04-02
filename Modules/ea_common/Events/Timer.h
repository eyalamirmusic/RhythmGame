#pragma once

#include "../Common/Common.h"
#include <juce_events/juce_events.h>

namespace EA::Events
{
class Timer : juce::Timer
{
public:
    Timer(const CallbackFunc& cbToUse, int hz = 60);
    ~Timer() override;

private:
    void timerCallback() override;

    CallbackFunc cb;
};
} // namespace EA::Events