#pragma once

#include "../Common/Common.h"

namespace EA::GUI::Scaling
{

Rectangle<float> scaleRect(const Rectangle<float>& source, const Rectangle<float>& ratio);

void scale(Component& comp, const Rectangle<float>& boundsRatio);
} // namespace EA::GUI::Scaling