#include "Flock.h"

#include <unordered_map>
#include <map>

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
    glm::vec2& orientation = orientations[id];
    orientation = inputOrientation;

    return std::make_unique<Boid>(position, orientation, size, resultingForce[id], id);
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
      glm::vec2& force = resultingForce[boid];
      std::vector<size_t> neighbors = allNeighbors[i];
      force = cohesion(neighbors);


    }
  }

  glm::vec2 Flock::alignment(const std::vector<size_t>& neighbors) {

  }

  glm::vec2 Flock::cohesion(const std::vector<size_t>& neighbors) {
    //Have each unit steer toward the average position of its neighbors.
    glm::vec2 result = glm::vec2(0, 0);
    for (const auto& neighbor : neighbors)
      result += positions[neighbor];
    result /= neighbors.size();
    return result;
  }

  void Flock::getActiveBoids(std::vector<size_t>& boids) {
    std::vector<size_t> boids;
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