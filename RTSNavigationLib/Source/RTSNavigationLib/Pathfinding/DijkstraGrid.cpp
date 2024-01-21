#include "DijkstraGrid.h"

#include <queue>

namespace RTSNavigationLib {
  DijkstraGrid::DijkstraGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution_, const glm::ivec2& target_) {
    target     = target_;
    resolution = resolution_;
    
    initGrid(obstacles);
  }

  float DijkstraGrid::getDistance(const glm::ivec2& position) const {
    size_t address = position.x % resolution.x + position.y * resolution.x;
    return grid[address];
  }

  void DijkstraGrid::initGrid(const std::vector<float>& obstacles) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    grid.resize(resolution.x * resolution.y, maxVal);
    
    auto compare = [](const std::pair<glm::ivec2, float>& a, const std::pair<glm::ivec2, float>& b) {
      return a.second < b.second; 
    };
    std::priority_queue<std::pair<glm::ivec2, float>, std::vector<std::pair<glm::ivec2, float>>, decltype(compare)> todo(compare);
    todo.push(std::make_pair(target,0));

    while (!todo.empty()) {
      const std::pair<glm::ivec2, float> current = todo.top();
      const glm::ivec2& pos = current.first;
      todo.pop();
      grid[pos.x + pos.y * resolution.x] = current.second;

      //add neighbours
      for (size_t i = 0; i < 8; i++) {
        size_t neighbhourIndex = i + i / 4;
        glm::ivec2 neighbourPos = pos + glm::ivec2(neighbhourIndex % 3 - 1, neighbhourIndex / 3 - 1);        

        //Boundary check
        if (neighbourPos.x < 0 ||
          neighbourPos.x >= resolution.x ||
          neighbourPos.y < 0 ||
          neighbourPos.y >= resolution.y) {
            continue;
        }

        //Process Neighbours
        size_t address = neighbourPos.x % resolution.x + neighbourPos.y * resolution.x;
        auto& neighbour = grid[address];
        const float& weight = obstacles[address];
        bool alreadyVisited = maxVal != neighbour;
        if (!alreadyVisited && std::isfinite(weight)) {
          float distance = current.second + weight;
          todo.push(std::make_pair(neighbourPos, distance));
        }
      }
    }
  }
}