#pragma once

#include "../Common/Common.h"

namespace EA::GUI
{
namespace Helpers
{
    Colour getDefaultBackgroundColor();


} // namespace Helpers

struct DefaultWindow : juce::DocumentWindow
{
    DefaultWindow(OwningPointer<Component> comp, const String& name = "");

    void closeButtonPressed() override {}
};

template <typename T>
struct BasicWindow
{
    template<typename ...Args>
    BasicWindow(const String& name = {}, Args&& ... args)
        : window(makeOwned<T>(std::forward<Args>(args)...), name)
    {
    }

    DefaultWindow window;
};
} // namespace EA::GUI