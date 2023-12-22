#include "RectangleGridSvg.h"

#include <glm/ext/scalar_constants.hpp>

#include "Util/svg.h"

namespace RTSPathingLib {
  std::vector<svg> RectangleGridSvg::write(const RectangleGrid<bool>& grid, double scale) {
    std::vector<svg> toWrite;
    std::vector<svg> overlay;
    for (size_t i = 0; i < grid.data.size(); i++) {
      svg v;
      glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, i / grid.dimension.x);
      glm::dvec2 rectCenter = glm::dvec2((pos.x+0.5)*scale,(pos.y+0.5)*scale) + grid.offset;
      v.streak = getRectangle(rectCenter, scale);
      v.filled = grid.data[i];
      toWrite.push_back(v);
      v.filled = false;
      v.color = "red";
      overlay.push_back(v);
    }
    toWrite.insert(toWrite.end(), overlay.begin(), overlay.end());
    return toWrite;
  }

  std::vector<glm::dvec2> RectangleGridSvg::getRectangle(const glm::dvec2& offset, double scale) {
    std::vector<glm::dvec2> result;
    result.push_back(offset + glm::dvec2(-0.5,-0.5) * scale);
    result.push_back(offset + glm::dvec2( 0.5,-0.5) * scale);
    result.push_back(offset + glm::dvec2( 0.5, 0.5) * scale);
    result.push_back(offset + glm::dvec2(-0.5, 0.5) * scale);
    result.push_back(result[0]);
    return result;
  }
}