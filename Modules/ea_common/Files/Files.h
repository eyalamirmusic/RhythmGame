#pragma once

#include "../Common/Common.h"

namespace juce
{
File operator/(File const& a, const String& b);
} // namespace juce

namespace EA::Files
{
File getDesktop();
} // namespace EA::Files