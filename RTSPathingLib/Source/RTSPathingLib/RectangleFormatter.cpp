#include "RectangleFormatter.h"

#include "Body.h"

namespace RTSPathingLib {
  RectangleFormatter::RectangleFormatter() {

  }
  std::vector<Body> RectangleFormatter::createRectGridFormation(const glm::ivec2& grid, const std::vector<size_t>& units, const std::vector<double>& unitRadiusPerID) {
    std::vector<Body> result;
    glm::ivec2 currentPosition = glm::ivec2(0, 0);
    double gridSize = 0;
    for (auto x : units)
      gridSize = std::max(gridSize, unitRadiusPerID[x]);

    for (auto x : units) {
      result.push_back(Body());
      Body& b = result.back();
      
      b.position = glm::dvec2(currentPosition[0]*gridSize, currentPosition[1]*gridSize);
      b.blueprintID = x;

      currentPosition.x++;
      if (currentPosition.x >= grid.x)
        currentPosition = glm::ivec2(0, currentPosition.y + 1);
    }

    return result;
  }
}