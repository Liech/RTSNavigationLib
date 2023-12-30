#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "TopFlatHexGrid.h"

namespace RTSPathingLib {
  class Hex2DVoxelizer {
  public:
    static TopFlatHexGrid<bool> voxelize(const std::vector<glm::dvec2>& polygon, const glm::ivec2& dimension, const glm::dvec2& offset, double scale = 1);
  };
}