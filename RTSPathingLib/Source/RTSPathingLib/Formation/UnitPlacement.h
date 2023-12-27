#pragma once

#include <vector>
#include <map>

#include "RTSPathingLib/Util/RectangleGrid/RectangleGrid.h"

namespace RTSPathingLib {
  struct Body;

  class UnitPlacement {
  public:
    UnitPlacement(const RectangleGrid<bool>&, const std::map<size_t, size_t>&, size_t);

    std::vector<Body> place(bool& success);

    RectangleGrid<bool> getUsedPositions() const;

  private:
    std::vector<Body> placeSizeN(size_t size, size_t amount, bool& success);
    std::vector<Body> placeSize1(bool& success);
    std::vector<glm::ivec2> getAllPlaces(const RectangleGrid<bool>&);

    std::vector<glm::ivec2> centerSort(const std::vector<glm::ivec2>&) const;
    std::vector<glm::ivec2> distributeSort(const std::vector<glm::ivec2>&, size_t desired) const;

    bool saveSVG = true;

    void saveAsSvg(const std::vector<Body>&);

    const RectangleGrid<bool>&      grid;
    const std::map<size_t, size_t>& unitsToPlace;
    RectangleGrid<bool>             usedPositions;
    size_t                          category;
    size_t                          smallestSize = 1;
  };
}