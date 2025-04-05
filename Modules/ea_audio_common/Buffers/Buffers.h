#pragma once

#include "../Common/Common.h"

namespace EA::Audio::Buffers
{
Buffer getSub(Buffer& source, int startSample, int length) noexcept;

void copy(const Buffer& source, Buffer& target) noexcept;
void mix(const Buffer& source, Buffer& target) noexcept;
void mixGain(const Buffer& source, Buffer& target, float gain) noexcept;
void copyToAllChannels(Buffer& buffer, int sourceChannel = 0) noexcept;

void clip(Buffer& buffer, float level = 1.f) noexcept;
} // namespace EA::Audio::Buffers