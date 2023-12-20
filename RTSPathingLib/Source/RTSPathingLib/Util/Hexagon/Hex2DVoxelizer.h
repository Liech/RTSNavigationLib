#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "TopFlatHexGrid.h"

namespace RTSPathingLib {
  class Hex2DVoxelizer {
  public:
    static TopFlatHexGrid<bool> voxelize(const std::vector<glm::vec2>& polygon, const glm::ivec2& dimension, const glm::vec2& offset, float scale = 1);

  private:
    static bool LineLineIntersect(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1, glm::vec2 q2, glm::vec2& intersection);
  };
}