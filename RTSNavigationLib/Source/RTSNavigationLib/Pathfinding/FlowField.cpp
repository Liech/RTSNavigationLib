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
    const auto result = lookup(symbol);
    return result;
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
      return glm::normalize(glm::dvec2(+1, +2));
    case 255:
      return glm::dvec2(0, 0);
    default:
      return glm::dvec2(0, 0);
    }
  }

  void FlowField::initField(const DijkstraGrid& grid) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    field.resize(resolution.x * resolution.y, 0);

    constexpr const std::array<glm::ivec2,8> neighbourOffset = {
      glm::ivec2(0,-1),glm::ivec2(-1,0),glm::ivec2(1,0),glm::ivec2(0,1),
      glm::ivec2(-1,-1),glm::ivec2(1,-1),glm::ivec2(-1,1),glm::ivec2(1,1),
    };
    constexpr const std::array<size_t,4> elementsWithPreconditions = {
      4,5,6,7
    };
    constexpr const std::array<size_t,8> converter8to16 = {
      4,7,8,11,3,5,10,12
    };

#pragma omp parallel for
    for (long long cell = 0; cell < field.size(); cell++) {
      float self = grid.getDistance(cell);
      if (self == 0.0f || self == maxVal) {
        field[cell] = 255;
        continue;
      }
       
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

    constexpr const std::array<glm::ivec2,24> neighbourOffset = {
      //Step0
      glm::ivec2(-1,0),glm::ivec2(1,0),glm::ivec2(0,1),glm::ivec2(0,-1),
      //Step1
      glm::ivec2(-1,-1),glm::ivec2(1,-1),glm::ivec2(-1,1),glm::ivec2(1,1),
      //Step2
      glm::ivec2(-2,0),glm::ivec2(2,0),glm::ivec2(0,2),glm::ivec2(0,-2),
      glm::ivec2(-2,-2),glm::ivec2(2,-2),glm::ivec2(-2,2),glm::ivec2(2,2),
      glm::ivec2(-1,-2),glm::ivec2(1,-2),glm::ivec2(-2,-1),glm::ivec2(2,-1),
      glm::ivec2(-2,1),glm::ivec2(2,1),glm::ivec2(-1,2),glm::ivec2(1,2),
      
    };
    constexpr const std::array<unsigned char, 24> convert2symbol {
      //Step0
      7,8,11,4,
      //Step1
      3,5,10,12,
      //Step2
      7,8,11,4,
      3,5,10,12,
      0,1,2,6,
      9,13,14,15

      //0N0N0
      //N3N5N
      //07X80
      //9NNNN
      //0N0N0
    };

#pragma omp parallel for
    for (long long cell = 0; cell < field.size(); cell++) {
      float self = grid.getDistance(cell);
      if (self == 0.0f || self == maxVal) {
        field[cell] = 255;
        continue;
      }

      size_t step = 0;
      size_t bestID = 255;
      float bestVal = self;
      long long x = cell % resolution.x;
      long long y = cell / resolution.x;
      bool anyWall = false;

      for (size_t i = 0; i < neighbourOffset.size(); i++) {
        if (i == 4 || i == 8) {
          step++;
          if (anyWall)
            break;
        }

        const auto& offset = neighbourOffset[i];
        auto pos = glm::ivec2(x, y) + offset;
        bool isInXBound = pos.x >= 0 && pos.x < resolution.x;
        bool isInYBound = pos.y >= 0 && pos.y < resolution.y;
        size_t address = cell + offset.x + offset.y * resolution.x;
        if (isInXBound && isInYBound) {
          const float& current = grid.getDistance(address);
          anyWall |= current == maxVal;
          if (bestVal > current) {
            bestID = i;
            bestVal = current;
          }
        }
        else
          anyWall = true;
      }

      field[cell] = convert2symbol[bestID]; //id can be converted via lookup table to vector
    }
  }
}