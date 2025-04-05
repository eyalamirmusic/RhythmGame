#include "DefaultWindow.h"

namespace EA::GUI
{
namespace Helpers

{
    static int getDefaultRequiredButtons()
    {
        using Win = juce::DocumentWindow;
        return Win::allButtons;
    }

    Colour getDefaultBackgroundColor()
    {
        auto& lnf = juce::Desktop::getInstance().getDefaultLookAndFeel();
        return lnf.findColour(juce::ResizableWindow::backgroundColourId);
    }
} // namespace Helpers

DefaultWindow::DefaultWindow(OwningPointer<Component> comp, const String& name)
    : DocumentWindow(name,
                     Helpers::getDefaultBackgroundColor(),
                     Helpers::getDefaultRequiredButtons())
{
    setContentOwned(comp.release(), true);
    DocumentWindow::setVisible(true);
}
} // namespace EA::GUI