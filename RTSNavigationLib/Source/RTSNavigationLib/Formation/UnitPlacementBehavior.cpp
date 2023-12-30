#include "UnitPlacementBehavior.h"

namespace RTSPathingLib {
  std::string UnitPlacementBehavior2String(const UnitPlacementBehavior& behavior) {
    switch (behavior) {
    case UnitPlacementBehavior::DistributeEvenly:
      return "Distribute";
    case UnitPlacementBehavior::OuterFirst:
      return "OuterFirst";
    case UnitPlacementBehavior::CenterFirst:
    default:
      return "CenterFirst";
    }
  }

  UnitPlacementBehavior String2UnitPlacementBehavior(const std::string& input) {
    if (input == "Distribute")
      return UnitPlacementBehavior::DistributeEvenly;
    else if (input == "OuterFirst")
      return UnitPlacementBehavior::OuterFirst;
    else
      return UnitPlacementBehavior::CenterFirst;
  }
}