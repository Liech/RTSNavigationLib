#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RTSNavigationLib {
  class HexGridUtils {
  public:
    static glm::dvec2 getTopFlatOffset(const glm::ivec2& position, const glm::dvec2& offset, double scale);
    static std::vector<glm::ivec2> getSurroundedTiles(glm::ivec2 pos);
  };
}