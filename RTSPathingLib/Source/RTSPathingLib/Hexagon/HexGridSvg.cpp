#include "HexGridSvg.h"

#include <glm/ext/scalar_constants.hpp>

#include "TopFlatHexGrid.h"
#include "Util/svg.h"

void HexGridSvg::write(const std::string& filename, const TopFlatHexGrid<bool>& grid) {
  for (size_t i = 0; i < grid.data.size(); i++) {

  }
  svg v;
  v.streak = getHexagon(glm::vec2(2.5, 2.5), 1);
  v.filled = true;
  v.write(filename, { v });
}

std::vector<glm::vec2> HexGridSvg::getHexagon(const glm::vec2& offset, float radius) {
  std::vector<glm::vec2> result;

  for (int i = 0; i < 6; i++) {
    glm::vec2 point;
    float angle = (i + 0.5) * 2.0f * glm::pi<float>() / 6.0f;
    point.x = radius * glm::cos(angle);
    point.y = radius * glm::sin(angle);
    result.push_back(point + offset);
  }
  return result;
}