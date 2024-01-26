#pragma once

#include <glm/glm.hpp>
#include <vector>

//https://howtorts.github.io/2013/12/31/generating-a-path-dijkstra.html

namespace RTSNavigationLib {
  class DijkstraGrid {
  public:
    DijkstraGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution, const glm::ivec2& target);

    glm::ivec2 getResolution() const;
    glm::ivec2 getTarget()     const;
    float getDistance(const glm::ivec2& position) const;
    float getDistance(const size_t& position) const;
  private:
    void initGrid(const std::vector<float>& obstacles);

    glm::ivec2 target;
    glm::ivec2 resolution;
    std::vector<float> grid;
  };
}