#pragma once

#include <glm/glm.hpp>

namespace RTSPathingLib {
  class Boid final {
  public:
    Boid(glm::vec2& position, size_t& size, glm::vec2& flockingForce, size_t id);
    ~Boid();

    glm::vec2& position;
    size_t&    size;

    glm::vec2 getFlockForce() const;
    size_t    getID() const;
  private:
    glm::vec2& resultingFlockForce;

    size_t id = 0;
  };
}