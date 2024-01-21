#include "Boid.h"

namespace RTSNavigationLib {
  Boid::Boid(glm::vec2& position_, glm::vec2& velocity_, size_t& size_, glm::vec2& cohesion, glm::vec2& alignment, glm::vec2& seperation, size_t id_) :
    position(position_),
    velocity(velocity_),
    size(size_), 
    cohesionForce(cohesion),
    alignmentForce(alignment),
    seperationForce(seperation),
    id(id_){
  }

  Boid::~Boid() {

  }

  glm::vec2 Boid::getCohesionForce() const {
    return cohesionForce;
  }

  glm::vec2 Boid::getAlignmentForce() const {
    return alignmentForce;
  }

  glm::vec2 Boid::getSeperationForce() const {
    return seperationForce;
  }

  size_t Boid::getID() const {
    return id;
  }
}