#pragma once

#include <glm/vec2.hpp>

template<typename T>
class HexGrid {
public:
  glm::ivec2 dimension;
  std::vector<T> data;
};