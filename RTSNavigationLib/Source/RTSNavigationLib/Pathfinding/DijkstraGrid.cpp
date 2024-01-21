#include "DijkstraGrid.h"

#include <queue>

namespace RTSNavigationLib {
  template<typename NumberType>
  DijkstraGrid<NumberType>::DijkstraGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution_, const glm::ivec2& target_) {
    assert(resolution.x * resolution.y < std::numeric_limits<NumberType>::max());
    target     = target_;
    resolution = resolution_;
    
    initGrid(obstacles);
  }

  template<typename NumberType>
  void DijkstraGrid<NumberType>::initGrid(const std::vector<float>& obstacles) {
    NumberType maxVal = std::numeric_limits<NumberType>::max();
    grid.resize(resolution.x * resolution.y, maxVal);

    std::queue<std::pair<glm::ivec2, NumberType>> todo;
    todo.push(std::make_pair(target,0));

    while (!todo.empty()) {
      const std::pair<glm::ivec2, NumberType> current = todo.front();
      const glm::ivec2& pos = current.first;
      todo.pop();
      grid[pos.x + pos.y * resolution.x] = current.second;

      //add neighbours
      for (size_t i = 0; i < 8; i++) {
        size_t neighbhourIndex = i + i / 4;
        glm::ivec2 neighbourPos = pos + glm::ivec2(neighbhourIndex % 3 - 1, neighbhourIndex / 3 - 1);        

        if (neighbourPos.x < 0 &&
          neighbourPos.x >= resolution.x &&
          neighbourPos.y < 0 &&
          neighbourPos.y >= resolution.y) {
            continue;
        }

        size_t address = neighbourPos.x % resolution.x + neighbourPos.y * resolution.x;
        auto& neighbour = grid[address];
        bool alreadyVisited = maxVal == neighbour;
        if (!alreadyVisited) {
          NumberType distance = current.second + 1;
          todo.push(std::make_pair(neighbourPos, distance));
          neighbour = distance;
        }
      }
    }
  }

  template struct DijkstraGrid<unsigned char>;
  template struct DijkstraGrid<unsigned int >;
}