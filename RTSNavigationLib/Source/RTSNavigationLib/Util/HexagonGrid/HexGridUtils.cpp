#include "HexGridUtils.h"

//https://www.redblobgames.com/grids/hexagons/

namespace RTSNavigationLib {
  glm::dvec2 HexGridUtils::getTopFlatOffset(const glm::ivec2& position, const glm::dvec2& offset, double scale) {
    double scaley = scale * (double)std::sqrt(3) * 0.5;
    double scalex = scale * 0.75;
    glm::dvec2 result = offset + glm::dvec2(position.x * scalex, position.y * scaley);
    if (position.x % 2 == 0)
      result += glm::dvec2(0.0, scaley * 0.5);
    return result;
  }

  std::vector<glm::ivec2> HexGridUtils::getSurroundedTiles(glm::ivec2 pos) {
    std::vector<glm::ivec2> result;
    result.push_back(pos + glm::ivec2(1, 0));
    result.push_back(pos + glm::ivec2(-1, 0));
    result.push_back(pos + glm::ivec2(((std::abs(pos.y % 2) == 0) ? -1 : 0), 1));
    result.push_back(pos + glm::ivec2(((std::abs(pos.y % 2) == 0) ? -1 : 0), -1));
    result.push_back(pos + glm::ivec2(((std::abs(pos.y % 2) == 1) ? 1 : 0), 1));
    result.push_back(pos + glm::ivec2(((std::abs(pos.y % 2) == 1) ? 1 : 0), -1));
    return result;
  }
}