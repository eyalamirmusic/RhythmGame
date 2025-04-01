#pragma once

#include "Common.h"

namespace EA::Platform
{
bool isMac();
bool isWindows();
bool isLinux();
bool isMobile();

bool isStandalone();
} // namespace EA::Platform