#pragma once

#include <glm/glm.hpp>

namespace RTSNavigationLib {
  struct glm2dBox
  {
    glm::dvec2 lowLeft;
    glm::dvec2 upRight;
    glm2dBox(double x1, double y1, double x2, double y2);
    glm2dBox(const glm::dvec2& lowLeft, const glm::dvec2& upRight);
  };
}