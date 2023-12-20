#pragma once

#include <string>
#include "RectangleGrid.h"

namespace RTSPathingLib {
  class svg;

  class RectangleGridSvg {
  public:
    static std::vector<svg> write(const RectangleGrid<bool>& grid, float scale = 1);

  private:
    static std::vector<glm::vec2> getRectangle(const glm::vec2& offset, float scale);
  };
}