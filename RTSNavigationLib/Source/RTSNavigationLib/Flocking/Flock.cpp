#include "Flock.h"

#include <unordered_map>
#include <map>

#include "Boid.h"

namespace RTSNavigationLib {
  Flock::Flock(const glm::ivec2& area_, double maxInfluenceRadius, size_t maxNumberOfBoids_) {
    maxNumberOfBoids = maxNumberOfBoids_;
    area             = area_;
    cellSize         = maxInfluenceRadius;

    isUsed         .resize(maxNumberOfBoids,false);
    sizes          .resize(maxNumberOfBoids);
    positions      .resize(maxNumberOfBoids);
    velocities     .resize(maxNumberOfBoids);
    cohesionForce  .resize(maxNumberOfBoids);
    seperationForce.resize(maxNumberOfBoids);
    alignmentForce .resize(maxNumberOfBoids);
    unusedIDs.reserve(1024);
    gridSize = glm::ivec2(std::ceil(area.x / (double)cellSize), std::ceil(area.y / (double)cellSize));
    hashgrid.resize(gridSize.x * gridSize.y);
    
    #pragma omp parallel for
    for (int64_t i = 0; i < hashgrid.size(); i++)
      hashgrid[i].reserve(16);
  }

  Flock::~Flock() {

  }

  std::unique_ptr<Boid> Flock::createBoid(const glm::vec2& inputPosition, const glm::vec2& inputOrientation, size_t inputSize) {
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
    glm::vec2& orientation = velocities[id];
    orientation = inputOrientation;

    return std::make_unique<Boid>(position, orientation, size, cohesionForce[id], alignmentForce[id], seperationForce[id], id);
  }
  
  void Flock::destroyBoid(const Boid& boid) {
    size_t id = boid.getID();
    isUsed[id] = false;
    unusedIDs.push_back(id);
  }

  void Flock::calculateForces() {
    std::vector<size_t> activeBoids;
    std::vector<size_t> gridAddressesForBoids;
    std::vector<std::vector<size_t>> neighbors;
    getActiveBoids(/*out*/activeBoids);
    updateHashgrid(activeBoids, /*out*/gridAddressesForBoids);
    gatherNeighbors(activeBoids, gridAddressesForBoids, /*out*/neighbors);
    applyForces(activeBoids, neighbors);
  }

  void Flock::applyForces(const std::vector<size_t>& boids, const std::vector<std::vector<size_t>>& allNeighbors) {
#pragma omp parallel for
    for (int64_t i = 0; i < boids.size(); i++) {
      size_t boid = boids[i];
      std::vector<size_t> neighbors = allNeighbors[i];
      cohesionForce  [boid] = cohesion  (boid, neighbors);
      seperationForce[boid] = seperation(boid, neighbors);
      alignmentForce [boid] = alignment (boid, neighbors);
    }
  }

  glm::vec2 Flock::alignment(size_t self, const std::vector<size_t>& neighbors) {
    if (neighbors.size() == 0)
      return glm::dvec2(0, 0);
    glm::vec2 velocityAverage = glm::vec2();
    for (const auto& id : neighbors) {
      velocityAverage += glm::normalize(velocities[id]);
    }
    velocityAverage /= neighbors.size();
    const glm::vec2& ownVelocity = glm::normalize(velocities[self]);
    
    return velocityAverage - ownVelocity;
  }

  glm::vec2 Flock::cohesion(size_t self, const std::vector<size_t>& neighbors) {
    //Have each unit steer toward the average position of its neighbors.
    if (neighbors.size() == 0)
      return glm::dvec2(0, 0);
    glm::vec2 result = glm::vec2(0, 0);
    for (const auto& neighbor : neighbors)
      result += positions[neighbor];
    result /= neighbors.size();
    const glm::vec2& ownPosition = positions[self];
    return result - ownPosition;
  }

  glm::vec2 Flock::seperation(size_t self, const std::vector<size_t>& neighbors) {
    //Have each unit steer toward the average position of its neighbors.
    if (neighbors.size() == 0)
      return glm::dvec2(0, 0);
    const glm::vec2& ownPosition = positions[self];
    glm::vec2 result = glm::vec2(0, 0);
    for (const auto& neighbor : neighbors) {
      auto dir = ownPosition - positions[neighbor];
      result += glm::normalize(dir) / glm::length(dir);
    }
    result = glm::normalize(result);
    return result;
  }

  void Flock::getActiveBoids(std::vector<size_t>& boids) {
    boids.clear();
    boids.reserve(maxID);
    for (size_t i = 0; i < maxID; i++)
      if (isUsed[i])
        boids.push_back(i);
  }

  void Flock::gatherNeighbors(const std::vector<size_t>& boids, const std::vector<size_t>& gridAdresses, std::vector<std::vector<size_t>>& neighbors) {
    neighbors.resize(boids.size());

    size_t maxGridAddress = gridSize.x * gridSize.y;
#pragma omp parallel for
    for (int64_t i = 0; i < boids.size(); i++) {
      size_t boid = boids[i];
      size_t address = gridAdresses[i];
      size_t up = address + gridSize.x;
      size_t down = address - gridSize.x;
      std::vector<size_t> cellsToSearch = { down-1,down,down+1,address-1,address,address+1,up-1,up,up+1 };
      for (size_t cell = 0; cell < 9; cell++) {
        size_t& cellAdress = cellsToSearch[cell];
        if (cellAdress >= maxGridAddress)
          continue;
        for (const auto& neighbor : hashgrid[cellAdress]) {
          if (boid == neighbor)
            continue;
          if (glm::distance(positions[boid], positions[neighbor]) < cellSize)
            neighbors[i].push_back(neighbor);
        }
      }
    }
  }

  void Flock::updateHashgrid(const std::vector<size_t>& boids, std::vector<size_t>& outBoidAddressesInGrid){
    outBoidAddressesInGrid.resize(boids.size());
#pragma omp parallel for
    for (int64_t i = 0; i < hashgrid.size(); i++)
      hashgrid[i].clear();

#pragma omp parallel for
    for (int64_t i = 0; i < boids.size(); i++) {
      const size_t&    id  = boids[i];
      const glm::vec2& pos = positions[id];

      size_t address = (size_t)(pos.x / cellSize) + (size_t)(pos.y / cellSize) * gridSize.x;
      outBoidAddressesInGrid[id] = address;
      std::vector<size_t>& cell = hashgrid[address];
#pragma omp atomic
      cell.push_back(i);
    }

  }
}