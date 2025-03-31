#include "Files.h"

namespace juce
{
File operator/(File const& a, const String& b)
{
    return a.getChildFile(b);
}
} // namespace juce

namespace EA::Files
{
File getDesktop()
{
    return File::getSpecialLocation(File::userDesktopDirectory);
}
} // namespace EA::Files
