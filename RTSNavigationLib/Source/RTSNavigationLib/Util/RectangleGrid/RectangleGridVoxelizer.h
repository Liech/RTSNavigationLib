#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "RectangleGrid.h"

namespace RTSPathingLib {
  class RectangleGridVoxelizer {
  public:
    static RectangleGrid<bool> voxelize(const std::vector<glm::dvec2>& polygon, const glm::ivec2& dimension, const glm::dvec2& offset, double scale = 1);
  };
}