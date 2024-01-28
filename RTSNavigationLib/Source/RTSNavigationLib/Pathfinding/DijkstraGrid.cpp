#include "DijkstraGrid.h"

#include <queue>
#include <array>

namespace RTSNavigationLib {
  DijkstraGrid::DijkstraGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution_, const std::vector<glm::ivec2>& targets_) {
    targets     = targets_;
    resolution = resolution_;
    assert(obstacles.size() == resolution.x * resolution.y);
    
    initGrid(obstacles);
  }

  float DijkstraGrid::getDistance(const glm::ivec2& position) const {
    size_t address = position.x % resolution.x + position.y * resolution.x;
    return grid[address];
  }

  float DijkstraGrid::getDistance(const size_t& address) const {
    return grid[address];
  }

  void DijkstraGrid::initGrid(const std::vector<float>& obstacles) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    grid.resize(resolution.x * resolution.y, maxVal);
    
    auto compare = [](const std::pair<glm::ivec2, float>& a, const std::pair<glm::ivec2, float>& b) {
      return a.second > b.second; 
    };
    std::priority_queue<std::pair<glm::ivec2, float>, std::vector<std::pair<glm::ivec2, float>>, decltype(compare)> todo(compare);
    for (const auto& target : targets) {
      todo.push(std::make_pair(target, 0.0f));
      grid[target.x + target.y * resolution.x] = 0.0f;
    }
    constexpr std::array<glm::ivec2, 4> neighbors = { glm::ivec2(-1,0),glm::ivec2(1,0),glm::ivec2(0,-1), glm::ivec2(0,1) };//, glm::ivec2(-1,-1), glm::ivec2(-1,1), glm::ivec2(1,-1), glm::ivec2(1,1)};

    while (!todo.empty()) {
      const std::pair<glm::ivec2, float> current = todo.top();
      const glm::ivec2& pos = current.first;
      todo.pop();

      for (const auto& neighbor : neighbors) {
        glm::ivec2 neighborPos = neighbor + pos;

        //Boundary check
        if (neighborPos.x < 0 ||
          neighborPos.x >= resolution.x ||
          neighborPos.y < 0 ||
          neighborPos.y >= resolution.y) {
          continue;
        }

        //Process Neighbours
        size_t address = neighborPos.x % resolution.x + neighborPos.y * resolution.x;
        auto& neighbour = grid[address];
        const float& weight = obstacles[address];
        bool alreadyVisited = maxVal != neighbour;
        if (!alreadyVisited && std::isfinite(weight)) {
          float distance = current.second + weight;
          todo.push(std::make_pair(neighborPos, distance));
          neighbour = distance;
        }
      }
    }
  }

  glm::ivec2 DijkstraGrid::getResolution() const {
    return resolution;
  }

  std::vector<glm::ivec2> DijkstraGrid::getTargets() const {
    return targets;
  }
}