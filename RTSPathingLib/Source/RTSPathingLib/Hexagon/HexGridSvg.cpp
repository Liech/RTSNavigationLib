#include "HexGridSvg.h"

#include <glm/ext/scalar_constants.hpp>

#include "TopFlatHexGrid.h"
#include "HexGridUtils.h"
#include "Util/svg.h"

std::vector<svg> HexGridSvg::write(const TopFlatHexGrid<bool>& grid, float scale) {  
  std::vector<svg> toWrite;
  std::vector<svg> overlay;
  for (size_t i = 0; i < grid.data.size(); i++) {
    svg v;
    glm::vec2 hexCenter = HexGridUtils::getTopFlatOffset(glm::ivec2(i % grid.dimension.x, i / grid.dimension.x), glm::vec2(0, 0), scale);
    v.streak = getHexagon(hexCenter, scale);
    v.filled = grid.data[i];
    toWrite.push_back(v);
    v.filled = false;
    v.color = "red";
    overlay.push_back(v);
  }
  toWrite.insert(toWrite.end(), overlay.begin(), overlay.end());
  return toWrite;
}

std::vector<glm::vec2> HexGridSvg::getHexagon(const glm::vec2& offset, float radius) {
  std::vector<glm::vec2> result;

  for (int i = 0; i < 7; i++) {
    glm::vec2 point;
    float angle = (i) * 2.0f * glm::pi<float>() / 6.0f;
    point.x = radius * glm::cos(angle) * 0.5f;
    point.y = radius * glm::sin(angle) * 0.5f;
    result.push_back(point + offset);
  }
  return result;
}