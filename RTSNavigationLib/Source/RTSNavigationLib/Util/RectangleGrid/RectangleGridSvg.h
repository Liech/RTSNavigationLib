#pragma once

#include <string>
#include "RectangleGrid.h"

namespace RTSNavigationLib {
  class svg;

  class RectangleGridSvg {
  public:
    static std::vector<svg> write(const RectangleGrid<bool>& grid, double scale = 1);

  private:
    static std::vector<glm::dvec2> getRectangle(const glm::dvec2& offset, double scale);
  };
}