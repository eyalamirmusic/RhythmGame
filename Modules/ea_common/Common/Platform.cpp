#include "Platform.h"

namespace EA::Platform
{

bool isMac()
{
#if JUCE_MAC
    return true;
#else
    return false;
#endif
}

bool isWindows()
{
#if JUCE_WINDOWS
    return true;
#else
    return false;
#endif
}
bool isLinux()
{
#if JUCE_LINUX
    return true;
#else
    return false;
#endif

}

bool isMobile()
{
#if JUCE_ANDROID || JUCE_IOS
    return true;
#else
    return false;
#endif
}

bool isStandalone()
{
#if JUCE_STANDALONE_APPLICATION
    return true;
#else
    return false;
#endif
}
} // namespace EA::Platform