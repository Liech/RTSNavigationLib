#pragma once

#include <string>
#include "TopFlatHexGrid.h"

class HexGridSvg {
public:
  static void write(const std::string& filename, const TopFlatHexGrid<bool>& grid);

private:
  static std::vector<glm::vec2> getHexagon(const glm::vec2& offset, float radius);
};