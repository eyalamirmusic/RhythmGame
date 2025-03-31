#pragma once

#include "../Common/Common.h"

namespace EA::Audio
{
class SmoothGain
{
public:
    void prepare(double sr, double time = 0.005);
    void setValueNow(float gain) noexcept;
    void disableNextSmoothing() noexcept;
    void process(Buffer& buffer, float gain) noexcept;

private:
    bool shouldSmooth = false;

    juce::SmoothedValue<float> smoother;
};
} // namespace EA::Audio