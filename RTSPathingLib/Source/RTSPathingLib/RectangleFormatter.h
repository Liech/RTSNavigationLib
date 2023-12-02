#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RTSPathingLib {
  class Body;

  class RectangleFormatter {
  public:
    RectangleFormatter();

    //Simplest formation: places units in grid of edge length 2*maxUnitRadius
    static std::vector<Body> createRectGridFormation(const glm::ivec2& grid, const std::vector<size_t>& units, const std::vector<double>& unitRadiusPerID);
  };
}