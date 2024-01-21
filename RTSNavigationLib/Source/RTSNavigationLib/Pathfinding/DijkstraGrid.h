#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RTSNavigationLib {
  template<typename NumberType = unsigned char>
  class DijkstraGrid {
  public:
    DijkstraGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution, const glm::ivec2& target);

  private:
    void initGrid(const std::vector<float>& obstacles);

    glm::ivec2 target;
    glm::ivec2 resolution;
    std::vector<NumberType> grid;
  };
}