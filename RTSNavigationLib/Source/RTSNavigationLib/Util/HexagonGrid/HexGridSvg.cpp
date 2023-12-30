#include "HexGridSvg.h"

#include <glm/ext/scalar_constants.hpp>

#include "TopFlatHexGrid.h"
#include "HexGridUtils.h"
#include "Util/svg.h"

namespace RTSPathingLib {
  std::vector<svg> HexGridSvg::write(const TopFlatHexGrid<bool>& grid, double scale) {
    std::vector<svg> toWrite;
    std::vector<svg> overlay;
    for (size_t i = 0; i < grid.data.size(); i++) {
      svg v;
      glm::dvec2 hexCenter = HexGridUtils::getTopFlatOffset(glm::ivec2(i % grid.dimension.x, i / grid.dimension.x), glm::dvec2(0, 0), scale);
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

  std::vector<glm::dvec2> HexGridSvg::getHexagon(const glm::dvec2& offset, double radius) {
    std::vector<glm::dvec2> result;

    for (int i = 0; i < 7; i++) {
      glm::dvec2 point;
      double angle = (i) * 2.0 * glm::pi<double>() / 6.0;
      point.x = radius * glm::cos(angle) * 0.5;
      point.y = radius * glm::sin(angle) * 0.5;
      result.push_back(point + offset);
    }
    return result;
  }
}