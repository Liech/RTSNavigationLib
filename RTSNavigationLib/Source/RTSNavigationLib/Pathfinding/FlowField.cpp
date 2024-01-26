#include "FlowField.h"

#include <array>

#include "DijkstraGrid.h"
#include "EikonalGrid.h"

namespace RTSNavigationLib {
  FlowField::FlowField(const DijkstraGrid& grid) {
    resolution = grid.getResolution();
    targets = grid.getTargets();
    initField(grid);
  }

  FlowField::FlowField(const EikonalGrid& grid) {
    resolution = grid.getResolution();
    targets = grid.getTargets();
    initField(grid);
  }

  glm::ivec2 FlowField::getResolution() const {
    return resolution;
  }

  std::vector<glm::ivec2> FlowField::getTargets() const {
    return targets;
  }

  glm::dvec2 FlowField::getDirection(const glm::ivec2& location) const {
    size_t address = location.x + location.y * resolution.x;
    unsigned char symbol = field[address];
    return lookup(symbol);
  }

  constexpr glm::dvec2 FlowField::lookup(unsigned char symbol) {
    //0N0N0
    //NNNNN
    //0NXN0
    //NNNNN
    //0N0N0
    switch (symbol) {
    case 0:
      return glm::normalize(glm::dvec2(-1,-2));
    case 1:
      return glm::normalize(glm::dvec2(+1,-2));

    case 2:
      return glm::normalize(glm::dvec2(-2,-1));
    case 3:
      return glm::normalize(glm::dvec2(-1,-1));
    case 4:
      return glm::normalize(glm::dvec2(+0,-1));
    case 5:
      return glm::normalize(glm::dvec2(+1,-1));
    case 6:
      return glm::normalize(glm::dvec2(+2,-1));

    case 7:
      return glm::normalize(glm::dvec2(-1,0));
    case 8:
      return glm::normalize(glm::dvec2(+1,0));

    case 9:
      return glm::normalize(glm::dvec2(-2, +1));
    case 10:
      return glm::normalize(glm::dvec2(-1, +1));
    case 11:
      return glm::normalize(glm::dvec2(+0, +1));
    case 12:
      return glm::normalize(glm::dvec2(+1, +1));
    case 13:
      return glm::normalize(glm::dvec2(+2, +1));

    case 14:
      return glm::normalize(glm::dvec2(-1,+2));
    case 15:
      return glm::normalize(glm::dvec2(+1,+2));
    }
    return glm::dvec2(0, 0);
  }

  void FlowField::initField(const DijkstraGrid& grid) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    field.resize(resolution.x * resolution.y, 0);

    constexpr const std::array<glm::ivec2,8> neighbourOffset = {
      glm::ivec2(-1,-1),glm::ivec2(0,-1),glm::ivec2(1,-1),//NNN
      glm::ivec2(-1,0),glm::ivec2(1,0),                   //NXN
      glm::ivec2(-1,1),glm::ivec2(0,1),glm::ivec2(1,1),   //NNN
    };
    constexpr const std::array<size_t,4> elementsWithPreconditions = {
      0,2,5,7
    };
    constexpr const std::array<size_t,8> converter8to16 = {
      3,4,5,7,8,10,11,12
    };

#pragma omp parallel for
    for (long long cell = 0; cell < field.size(); cell++) {
      std::array<float, 8> neighbors;
      long long x = cell % resolution.x;
      long long y = cell / resolution.x;
      bool anyWall = false;
      for (size_t i = 0; i < 8; i++) {
        const auto& offset = neighbourOffset[i];
        auto pos = glm::ivec2(x, y) + offset;
        bool isInXBound = pos.x >= 0 && pos.x < resolution.x;
        bool isInYBound = pos.y >= 0 && pos.y < resolution.y;
        size_t address = cell + offset.x + offset.y * resolution.x;
        if (isInXBound && isInYBound)
          neighbors[i] = grid.getDistance(address);
        else
          neighbors[i] = maxVal;
        anyWall |= neighbors[i] == maxVal;
      }

      //preconditions
      if (anyWall) {
        for (const size_t& element : elementsWithPreconditions)
          neighbors[element] = maxVal;
      }

      //select result
      size_t bestID = 0;
      float bestVal = neighbors[0];
      for (size_t i = 0; i < 8; i++) {
        const float& current = neighbors[i];
        if (bestVal > current) {
          bestID = i;
          bestVal = current;
        }
      }
      field[cell] = converter8to16[bestID]; //id can be converted via lookup table to vector
    }
  }

  void FlowField::initField(const EikonalGrid& grid) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    field.resize(resolution.x * resolution.y, 0);

    constexpr const std::array<glm::ivec2,16> neighbourOffset = {
      glm::ivec2(-1,-2),glm::ivec2(1,-2),                                                    //0N0N0
      glm::ivec2(-2,-1),glm::ivec2(-1,-1),glm::ivec2(0,-1),glm::ivec2(1,-1),glm::ivec2(2,-1),//NNNNN
      glm::ivec2(-1,0),glm::ivec2(1,0),                                                      //0NXN0
      glm::ivec2(-2,1),glm::ivec2(-1,1),glm::ivec2(0,1),glm::ivec2(1,1),glm::ivec2(2,1),     //NNNNN
      glm::ivec2(-1,2),glm::ivec2(-1,2),                                                     //0N0N0
    };
    constexpr const std::array<size_t,8> mustFreeAreas{
      3,4,5,7,8,10,11,12
    };
    constexpr const std::array<size_t,12> elementsWithPreconditions = {
      0,1,2,3, 5,6,9,10 ,12,13,14,15
    };

#pragma omp parallel for
    for (long long cell = 0; cell < field.size(); cell++) {
      std::array<float, 16> neighbors;  
      long long x = cell % resolution.x;
      long long y = cell / resolution.x;
      for (size_t i = 0; i < 16; i++) {
        const auto& offset = neighbourOffset[i];
        auto pos = glm::ivec2(x, y) + offset;
        bool isInXBound = pos.x >= 0 && pos.x < resolution.x;
        bool isInYBound = pos.y >= 0 && pos.y < resolution.y;
        size_t address = cell + offset.x + offset.y * resolution.x;
        if (isInXBound && isInYBound)
          neighbors[i] = grid.getDistance(address);
        else
          neighbors[i] = maxVal;
      }

      //preconditions
      bool freeCenter = true;
      for (const size_t& element : mustFreeAreas) {
          freeCenter &= neighbors[element] != maxVal;
      }
      if (!freeCenter) {
        for (const size_t& element : elementsWithPreconditions)
          neighbors[element] = maxVal;
      }

      //select result
      size_t bestID = 0;
      float bestVal = neighbors[0];
      for (size_t i = 0; i < 16; i++) {
        const float& current = neighbors[i];
        if (bestVal > current) {
          bestID = i;
          bestVal = current;
        }
      }
      field[cell] = bestID; //id can be converted via lookup table to vector
    }
  }
}