#pragma once

#include <string>
#include "TopFlatHexGrid.h"

class svg;

class HexGridSvg {
public:
  static std::vector<svg> write(const TopFlatHexGrid<bool>& grid, float scale = 1);

private:
  static std::vector<glm::vec2> getHexagon(const glm::vec2& offset, float radius);
};