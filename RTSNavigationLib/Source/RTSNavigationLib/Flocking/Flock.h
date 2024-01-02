#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <glm/glm.hpp>

//https://www.oreilly.com/library/view/ai-for-game/0596005555/ch04.html
//https://code.tutsplus.com/3-simple-rules-of-flocking-behaviors-alignment-cohesion-and-separation--gamedev-3444t

namespace RTSPathingLib {
  class Boid;

  //find registered entities surrounding eachother via spatial hashing
  //in this class performance is more important than standards, readablity or safety. I hope it is worth it :x
  class Flock final {
  public:
    Flock(const glm::ivec2& area, size_t maxInfluenceRadius, size_t maxNumberOfBoids = 50000);
    ~Flock();

    void calculateForces();

    std::unique_ptr<Boid> createBoid(const glm::vec2& position, const glm::vec2& orientation, size_t size);
    void                  destroyBoid(const Boid&);

  private:
    void updateHashgrid(const std::vector<size_t>& boids, std::vector<size_t>& outBoidAddressesInGrid);
    void gatherNeighbors(const std::vector<size_t>& boids, const std::vector<size_t>& outBoidAddressesInGrid,std::vector<std::vector<size_t>>& neighbors);
    void getActiveBoids(std::vector<size_t>& outActive);
    void applyForces(const std::vector<size_t>& boids, const std::vector<std::vector<size_t>>& neighbors);

    glm::vec2 cohesion(size_t self, const std::vector<size_t>& neighbors);
    glm::vec2 alignment(size_t self, const std::vector<size_t>& neighbors);
    glm::vec2 seperation(size_t self, const std::vector<size_t>& neighbors);

    size_t maxNumberOfBoids = 50000;

    std::vector<size_t   > unusedIDs;
    size_t maxID = 0;

    std::vector<bool     > isUsed    ;
    std::vector<size_t   > sizes     ;
    std::vector<glm::vec2> positions ;
    std::vector<glm::vec2> velocities;
    std::vector<glm::vec2> resultingForce;

    std::vector<std::vector<size_t>> hashgrid;
    glm::ivec2                       area;
    size_t                           cellSize;
    glm::ivec2                       gridSize;
  };
}