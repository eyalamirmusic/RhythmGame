#pragma once

#if 0

BEGIN_JUCE_MODULE_DECLARATION

      ID:               ea_audio_common
      vendor:           Eyal Amir
      version:          0.0.1
      name:             ea_audio_common
      description:      EA Audio Common
      license:          GPL/Commercial
      dependencies:     juce_audio_utils ea_common

     END_JUCE_MODULE_DECLARATION

#endif

#include "ProcessorBase/ProcessorBase.h"
#include "BasicSynth/BasicSynth.h"
#include "Buffers/SmoothGain.h"

#include "MIDIPlayer/MIDIPlayer.h"