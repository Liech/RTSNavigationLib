#include "FlowField.h"

#include <set>

namespace RTSPathingLib {
  FlowField::FlowField(const std::vector<float>& obstacles, const glm::ivec2& resolution_, const glm::ivec2& target_) {
    resolution = resolution_;
    target     = target_;

    initField(obstacles);
  }

  glm::dvec2 FlowField::getDirection(const glm::ivec2& location) const {
    size_t address = location.x + location.y * resolution.x;
    return field[address];
  }

  void FlowField::initField(const std::vector<float>& obstacles) {
    field.resize(resolution.x * resolution.y, glm::vec2(0, 0));

    std::set<glm::ivec2>    done;
    std::vector<glm::ivec2> todo;
    todo.reserve(2*(resolution.x + resolution.y)); //guesstimate: surface area of rectangle
    todo.push_back(target);

    while (!todo.empty()) {
      glm::ivec2 current = todo.front();
      break;
    }
  }
}