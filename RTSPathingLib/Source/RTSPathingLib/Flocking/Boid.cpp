#include "Boid.h"

namespace RTSPathingLib {
  Boid::Boid(glm::vec2& position_, size_t& size_, glm::vec2& flockingForce, size_t id_) :
    position(position_),
    size(size_), 
    resultingFlockForce(flockingForce),
    id(id_){
  }

  Boid::~Boid() {

  }

  glm::vec2 Boid::getFlockForce() const {
    return resultingFlockForce;
  }

  size_t Boid::getID() const {
    return id;
  }
}