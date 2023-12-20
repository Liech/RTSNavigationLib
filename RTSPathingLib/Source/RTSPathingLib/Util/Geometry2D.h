#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RTSPathingLib {
  class Geometry2D {
  public:
    static bool LineLineIntersect(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1, glm::vec2 q2, glm::vec2& intersection);
  };
}