#include "HexGridUtils.h"

//https://www.redblobgames.com/grids/hexagons/

namespace RTSPathingLib {
  glm::vec2 HexGridUtils::getTopFlatOffset(const glm::ivec2& position, const glm::vec2& offset, float scale) {
    float scaley = scale * (float)std::sqrt(3) * 0.5f;
    float scalex = scale * 0.75f;
    glm::vec2 result = offset + glm::vec2(position.x * scalex, position.y * scaley);
    if (position.x % 2 == 0)
      result += glm::vec2(0.0f, scaley * 0.5f);
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