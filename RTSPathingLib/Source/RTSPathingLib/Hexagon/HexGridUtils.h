#pragma once

#include <glm/glm.hpp>
#include <vector>

class HexGridUtils {
public:
  static glm::vec2 getTopFlatOffset(const glm::ivec2& position, const glm::vec2& offset, float scale);
  static std::vector<glm::ivec2> getSurroundedTiles(glm::ivec2 pos);
};