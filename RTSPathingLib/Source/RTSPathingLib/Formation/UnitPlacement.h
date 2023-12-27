#pragma once

#include <vector>
#include <map>

#include "RTSPathingLib/Util/RectangleGrid/RectangleGrid.h"

namespace RTSPathingLib {
  struct Body;

  class UnitPlacement {
  public:
    UnitPlacement(RectangleGrid<bool>&, const std::map<size_t, size_t>&, size_t);

    std::vector<Body> place(bool& success) const;

  private:
    RectangleGrid<bool>&            grid;
    const std::map<size_t, size_t>& unitsToPlace;
    size_t                          category;
  };
}