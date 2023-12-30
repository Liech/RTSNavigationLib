#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <glm/glm.hpp>

namespace RTSPathingLib {
  class Boid;

  //find registered entities surrounding eachother via spatial hashing
  //in this class performance is more important than standards, readablity or safety. I hope it is worth it :x
  class Flock final {
  public:
    Flock(const glm::ivec2& area, size_t maxInfluenceRadius, size_t maxNumberOfBoids = 50000);
    ~Flock();

    void calculateForces();

    std::unique_ptr<Boid> createBoid(const glm::vec2& position, size_t size);
    void                  destroyBoid(const Boid&);

  private:
    void updateHashgrid();

    size_t maxNumberOfBoids = 50000;

    std::vector<size_t   > unusedIDs;
    size_t maxID = 0;

    std::vector<bool     > isUsed        ;
    std::vector<size_t   > sizes         ;
    std::vector<glm::vec2> positions     ;
    std::vector<glm::vec2> resultingForce;

    std::vector<std::vector<size_t>> hashgrid;
    glm::ivec2                       area;
    size_t                           cellSize;
    glm::ivec2                       gridSize;
  };
}