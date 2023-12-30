#pragma once

#include <string>

namespace RTSPathingLib {
  enum class ScalingBehavior {
    PureX, PureY, Isotropic, X75Y25, X25Y75
  };

  ScalingBehavior String2ScalingBehavior(const std::string&);
  std::string ScalingBehavior2String(ScalingBehavior);
}