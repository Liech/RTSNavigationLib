#pragma once

#include <string>

namespace RTSPathingLib {
  enum class UnitPlacementBehavior {
    CenterFirst, OuterFirst, DistributeEvenly
  };

  std::string UnitPlacementBehavior2String(const UnitPlacementBehavior&);
  UnitPlacementBehavior String2UnitPlacementBehavior(const std::string&);
}