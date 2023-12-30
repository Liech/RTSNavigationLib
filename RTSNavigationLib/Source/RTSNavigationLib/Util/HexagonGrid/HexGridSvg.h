#pragma once

#include <string>
#include "TopFlatHexGrid.h"

namespace RTSPathingLib {
  class svg;

  class HexGridSvg {
  public:
    static std::vector<svg> write(const TopFlatHexGrid<bool>& grid, double scale = 1);

  private:
    static std::vector<glm::dvec2> getHexagon(const glm::dvec2& offset, double radius);
  };
}