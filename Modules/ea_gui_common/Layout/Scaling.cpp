#include "Scaling.h"

namespace EA::GUI::Scaling
{

static AffineTransform getRectTransform(const Rectangle<float>& source,
                                        const Rectangle<float>& target)
{
    float newX = target.getX();
    float newY = target.getY();

    float scaleX = target.getWidth() / source.getWidth();
    float scaleY = target.getHeight() / source.getHeight();

    auto transform = AffineTransform::translation(-source.getX(), -source.getY())
                         .scaled(scaleX, scaleY)
                         .translated(newX, newY);

    jassert(!std::isnan(transform.mat01));
    jassert(!std::isnan(transform.mat02));

    return transform;
}


static void setTransformedBounds(Component& comp, const Rectangle<float>& bounds)
{
    auto compBounds = bounds.toNearestInt();
    auto canTransform = compBounds.getWidth() > 0 && compBounds.getHeight() > 0;

    if (canTransform)
    {
        auto transform = getRectTransform(compBounds.toFloat(), bounds);

        comp.setTransform(AffineTransform());
        comp.setBounds(compBounds);
        comp.setTransform(transform);
    }
    else
        comp.setBounds(compBounds);
}

static void scale(Component& comp,
                  const Rectangle<float>& boundsSource,
                  const Rectangle<float>& boundsRatio)
{
    if (boundsSource.isEmpty() || boundsRatio.isEmpty())
        return;

    auto scaledBounds = scaleRect(boundsSource, boundsRatio);

    setTransformedBounds(comp, scaledBounds);
}

Rectangle<float> scaleRect(const Rectangle<float>& source, const Rectangle<float>& ratio)
{
    auto newWidth = source.getWidth() * ratio.getWidth();
    auto newHeight = source.getHeight() * ratio.getHeight();
    auto newX = source.getX() + (ratio.getX() * source.getWidth());
    auto newY = source.getY() + (ratio.getY() * source.getHeight());

    return {newX, newY, newWidth, newHeight};
}

void scale(Component& comp, const Rectangle<float>& boundsRatio)
{
    if (auto* parent = comp.getParentComponent())
    {
        auto parentBounds = parent->getLocalBounds().toFloat();
        scale(comp, parentBounds, boundsRatio);
    }
}

void resizeVertically(Component& comp)
{
    auto y = 0.f;
    auto width = 1.f / (float) comp.getChildren().size();

    for (auto& child: comp.getChildren())
    {
        scale(*child, {0.f, y, 1.f, width});
        y += width;
    }
}
} // namespace EA::GUI::Scaling
