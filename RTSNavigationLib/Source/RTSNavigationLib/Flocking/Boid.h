#pragma once

#include <glm/glm.hpp>

namespace RTSPathingLib {
  class Boid final {
  public:
    Boid(glm::vec2& position, glm::vec2& velocity, size_t& size, glm::vec2& cohesion, glm::vec2& alignment, glm::vec2& seperation, size_t id);
    ~Boid();

    glm::vec2& position;
    glm::vec2& velocity;
    size_t&    size;

    glm::vec2 getCohesionForce() const;
    glm::vec2 getAlignmentForce() const;
    glm::vec2 getSeperationForce() const;
    size_t    getID() const;
  private:
    glm::vec2& cohesionForce;
    glm::vec2& alignmentForce;
    glm::vec2& seperationForce;

    size_t id = 0;
  };
}