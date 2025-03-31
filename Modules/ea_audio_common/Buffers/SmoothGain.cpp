#include "SmoothGain.h"

namespace EA::Audio
{
void SmoothGain::prepare(double sr, double time)
{
    smoother.reset(sr, time);
    disableNextSmoothing();
}

void SmoothGain::setValueNow(float gain) noexcept
{
    smoother.setCurrentAndTargetValue(gain);
    shouldSmooth = true;
}

void SmoothGain::disableNextSmoothing() noexcept
{
    shouldSmooth = false;
}

void SmoothGain::process(Buffer& buffer, float gain) noexcept
{
    if (shouldSmooth)
        smoother.setTargetValue(gain);
    else
        setValueNow(gain);

    smoother.applyGain(buffer, buffer.getNumSamples());
}
} // namespace EA::Audio
