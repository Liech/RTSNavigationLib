#pragma once

#include <glm/glm.hpp>

namespace RTSPathingLib {
  struct glm2dBox
  {
    glm::vec2 lowLeft;
    glm::vec2 upRight;
    glm2dBox(float x1, float y1, float x2, float y2);
    glm2dBox(const glm::vec2& lowLeft, const glm::vec2& upRight);
  };
}