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
    std::vector<Body> placeSizeN(size_t size, size_t amount, bool& success) const;
    std::vector<Body> placeSize1(bool& success) const;
    std::vector<glm::ivec2> getAllPlaces(const RectangleGrid<bool>&) const;

    RectangleGrid<bool>&            grid;
    const std::map<size_t, size_t>& unitsToPlace;
    size_t                          category;
  };
}