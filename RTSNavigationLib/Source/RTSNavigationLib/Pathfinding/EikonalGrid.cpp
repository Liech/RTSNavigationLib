#include "EikonalGrid.h"

#include <queue>
#include <array>

namespace RTSNavigationLib {
  EikonalGrid::EikonalGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution_, const std::vector<glm::ivec2>& targets_) {
    targets = targets_;
    resolution = resolution_;

    initGrid(obstacles);
  }

  float EikonalGrid::getDistance(const glm::ivec2& position) const {
    size_t address = position.x % resolution.x + position.y * resolution.x;
    return grid[address];
  }

  float EikonalGrid::getDistance(const size_t& address) const {
    return grid[address];
  }

  float EikonalGrid::getWeight(const glm::ivec2& pos, const std::vector<float>& obstacles) const {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    constexpr float boundary = 0;

    bool validXM = pos.x > 0;
    bool validYM = pos.y > 0;
    bool validXP = pos.x < resolution.x - 1;
    bool validYP = pos.y < resolution.y - 1;

    size_t Self = pos.x % resolution.x + pos.y * resolution.x;
    size_t XM = Self - 1;
    size_t XP = Self + 1;
    size_t YM = pos.x % resolution.x + (pos.y - 1) * resolution.x;
    size_t YP = pos.x % resolution.x + (pos.y + 1) * resolution.x;

    float weightXM = validXM ? grid[XM] : boundary;
    float weightYM = validYM ? grid[YM] : boundary;
    float weightXP = validXP ? grid[XP] : boundary;
    float weightYP = validYP ? grid[YP] : boundary;
    float weightSelf = obstacles[Self];

    float dx = std::min(weightXM, weightXP);
    float dy = std::min(weightYM, weightYP);
    float Delta = 2.0f * weightSelf - std::pow((dx - dy), 2);

    if (Delta >= 0)
      return (dx + dy + sqrt(Delta)) / 2;
    else
      return std::min(dx + weightSelf, dy + weightSelf);
  }

  void EikonalGrid::initGrid(const std::vector<float>& obstacles) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    grid.resize(resolution.x * resolution.y, maxVal);

    auto compare = [](const std::pair<glm::ivec2, float>& a, const std::pair<glm::ivec2, float>& b) {
      return a.second > b.second;
    };
    std::priority_queue<std::pair<glm::ivec2, float>, std::vector<std::pair<glm::ivec2, float>>, decltype(compare)> todo(compare);
    for(const auto& target : targets) {
      todo.push(std::make_pair(target, 0.0f));
      grid[target.x + target.y * resolution.x] = 0.0f;
    }

    while (!todo.empty()) {
      const std::pair<glm::ivec2, float> current = todo.top();
      const glm::ivec2& pos = current.first;
      todo.pop();

      constexpr std::array<glm::ivec2, 4> neighbors = { glm::ivec2(-1,0), glm::ivec2(1,0),glm::ivec2(0,-1),glm::ivec2(0,1) };
      //add neighbours
      for (size_t i = 0; i < 4; i++) {
        glm::ivec2 neighbourPos = pos + neighbors[i];

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
        const float& weight = getWeight(neighbourPos, obstacles);
        bool alreadyVisited = maxVal != neighbour;
        if (!alreadyVisited && std::isfinite(weight)) {
          float distance = current.second + weight;
          todo.push(std::make_pair(neighbourPos, distance));
          neighbour = distance;
        }
      }
    }
  }

  glm::ivec2 EikonalGrid::getResolution() const {
    return resolution;
  }

  std::vector<glm::ivec2> EikonalGrid::getTargets() const {
    return targets;
  }
}