#include "Flock.h"

#include "Boid.h"

namespace RTSPathingLib {
  Flock::Flock(const glm::ivec2& area_, size_t maxInfluenceRadius, size_t maxNumberOfBoids_) {
    maxNumberOfBoids = maxNumberOfBoids_;
    area             = area_;
    cellSize         = maxInfluenceRadius;

    isUsed        .resize(maxNumberOfBoids,false);
    sizes         .resize(maxNumberOfBoids);
    positions     .resize(maxNumberOfBoids);
    resultingForce.resize(maxNumberOfBoids);
    unusedIDs.reserve(1024);
    gridSize = glm::ivec2(std::ceil(area.x / (double)cellSize), std::ceil(area.y / (double)cellSize));
    hashgrid.resize(gridSize.x * gridSize.y);
    
    #pragma omp parallel for
    for (int64_t i = 0; i < hashgrid.size(); i++)
      hashgrid[i].reserve(16);
  }

  Flock::~Flock() {

  }

  std::unique_ptr<Boid> Flock::createBoid(const glm::vec2& inputPosition, size_t inputSize) {
    size_t id = maxID;
    if (unusedIDs.size() > 0) {
      id = unusedIDs.back();
      unusedIDs.pop_back();
    }
    else
      maxID++;

    isUsed[id] = true;
    glm::vec2& position = positions[id];
    position = inputPosition;
    size_t& size = sizes[id];
    size = inputSize;

    return std::make_unique<Boid>(position, size, resultingForce[id], id);
  }
  
  void Flock::destroyBoid(const Boid& boid) {
    size_t id = boid.getID();
    isUsed[id] = false;
    unusedIDs.push_back(id);
  }

  void Flock::calculateForces() {
    updateHashgrid();
  }

  void Flock::updateHashgrid(){
    std::vector<size_t> boids;
    boids.reserve(maxID);
    for (size_t i = 0; i < maxID; i++)
      if (isUsed[i])
        boids.push_back(i);

#pragma omp parallel for
    for (int64_t i = 0; i < hashgrid.size(); i++)
      hashgrid[i].clear();

#pragma omp parallel for
    for (int64_t i = 0; i < boids.size(); i++) {
      const size_t&    id  = boids[i];
      const glm::vec2& pos = positions[id];

      size_t address = (size_t)(pos.x / cellSize) + (size_t)(pos.y / cellSize) * gridSize.x;
      std::vector<size_t>& cell = hashgrid[address];
#pragma omp atomic
      cell.push_back(i);
    }

  }
}