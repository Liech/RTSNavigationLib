#include "GridOfGrids.h"

namespace RTSNavigationLib {
  GridOfGrids::GridOfGrids(const std::vector<float>& obstacles_, const glm::ivec2& resolution_, const glm::ivec2& subResolution_, size_t overlap_) :
    obstacles(obstacles_),
    resolution(resolution_),
    subResolution(subResolution_),
    overlap(overlap_)
  {
    gridSize = glm::ivec2(std::ceil(resolution.x/subResolution.x), std::ceil(resolution.y / subResolution.y));
    initUnawarePortals();
  }

  void GridOfGrids::initUnawarePortals() {
    portals.resize((gridSize.x - 1) * (gridSize.y - 1) * 2);
    for (size_t i = 0; i < portals.size(); i++) {
      glm::ivec2 grid = glm::ivec2((i / 2) % gridSize.x, (i / 2) / resolution.x);
      bool odd = i % 2 == 1;
      glm::ivec2 start   = glm::ivec2(subResolution.x * (grid.x - odd?0:1), subResolution.y * (grid.y - odd ? 1 : 0));
      glm::ivec2 end = glm::ivec2(subResolution.x * (grid.x+1), subResolution.y * (grid.y+1));
      portals[i].push_back(std::make_pair(start, end));
    }
  }
}