#pragma once

#include <glm/vec2.hpp>
#include <vector>

namespace RTSPathingLib {
  template<typename T>
  class RectangleGrid {
  public:
    glm::ivec2 dimension = glm::ivec2(1,1);
    std::vector<T> data;
    glm::dvec2 offset = glm::dvec2(0, 0);
  };
}