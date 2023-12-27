#include "UnitPlacement.h"

#include "Body.h"

namespace RTSPathingLib {
  UnitPlacement::UnitPlacement(RectangleGrid<bool>& unitGrid, const std::map<size_t, size_t>& unitList, size_t category_) : 
  grid(unitGrid),
  unitsToPlace(unitList){
    category = category_;
  }

  std::vector<Body> UnitPlacement::place(bool& success) const {
    success = false;

    std::vector<Body> result;
    size_t currentSize = 1;
    RectangleGrid<bool> actuallyPlaced;
    actuallyPlaced.dimension = grid.dimension;
    actuallyPlaced.offset = grid.offset;
    actuallyPlaced.data.resize(grid.data.size());
    long long amountUnits = (long long)unitsToPlace.at(currentSize);
    for (size_t i = 0; i < grid.data.size() && amountUnits>0; i++) {
      if (grid.data[i]) {
        glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, (i / grid.dimension.x) % grid.dimension.y);
        Body sub;
        sub.category = category;
        sub.size = currentSize;
        sub.position = (glm::dvec2)pos + (glm::dvec2)grid.offset + glm::dvec2(0.5, 0.5);
        result.push_back(sub);
        actuallyPlaced.data[i] = true;
        amountUnits--;
      }
    }
    if (amountUnits <= 0)
      success = true;
    grid = actuallyPlaced;
    return result;
  }
}