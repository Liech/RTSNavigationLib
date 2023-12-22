#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RTSPathingLib {
  class Geometry2D {
  public:
    static bool LineLineIntersect(glm::dvec2 p1, glm::dvec2 p2, glm::dvec2 q1, glm::dvec2 q2, glm::dvec2& intersection);
  };
}