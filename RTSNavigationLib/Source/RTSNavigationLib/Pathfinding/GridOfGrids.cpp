#include "GridOfGrids.h"

namespace RTSNavigationLib {
  GridOfGrids::GridOfGrids(const std::vector<float>& obstacles_, const glm::ivec2& resolution_, const glm::ivec2& subResolution_, size_t overlap_) :
    obstacles(obstacles_),
    resolution(resolution_),
    subResolution(subResolution_),
    overlap(overlap_)
  {
    
  }
}