#pragma once

#include "../Common/Common.h"

namespace EA::Audio::Buffers
{
Buffer getSub(Buffer& source, int startSample, int length) noexcept;

void copyToAllChannels(Buffer& buffer, int sourceChannel = 0) noexcept;
} // namespace EA::Audio::Buffers