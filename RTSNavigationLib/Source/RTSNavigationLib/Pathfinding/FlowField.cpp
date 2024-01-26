#include "FlowField.h"

#include <array>

#include "DijkstraGrid.h"
#include "EikonalGrid.h"

namespace RTSNavigationLib {
  FlowField::FlowField(const DijkstraGrid& grid) {
    resolution = grid.getResolution();
    target = grid.getTarget();

    int r = resolution.x;
    std::vector<int> neighbours9 = { 
      -r - 1,-r,-r+1,//0NNN0
      -1,1,          //0NXN0
      r-1,r,r+1      //0NNN0
    };

    initField(grid);
  }

  FlowField::FlowField(const EikonalGrid& grid) {
    resolution = grid.getResolution();
    target = grid.getTarget();


    initField(grid);
  }

  glm::ivec2 FlowField::getResolution() const {
    return resolution;
  }

  glm::ivec2 FlowField::getTarget() const {
    return target;
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
    field.resize(resolution.x * resolution.y, 0);

  }

  void FlowField::initField(const EikonalGrid& grid) {
    constexpr float maxVal = std::numeric_limits<float>::infinity();
    field.resize(resolution.x * resolution.y, 0);

    int r = resolution.x;
    const std::vector<glm::ivec2> neighbourOffset = {
      glm::ivec2(-1,-2),glm::ivec2(1,-2),                                                    //0N0N0
      glm::ivec2(-2,-1),glm::ivec2(-1,-1),glm::ivec2(0,-1),glm::ivec2(1,-1),glm::ivec2(2,-1),//NNNNN
      glm::ivec2(-1,0),glm::ivec2(1,0),                                                      //0NXN0
      glm::ivec2(-2,1),glm::ivec2(-1,1),glm::ivec2(0,1),glm::ivec2(1,1),glm::ivec2(2,1),     //NNNNN
      glm::ivec2(-1,2),glm::ivec2(-1,2),                                                     //0N0N0
    };
    const std::vector<std::vector<size_t>> mustFreeAreas{
      //first one is a must, one of second or third must also
      //A
      {3,4,7}, //0N0N0    counting Ns
               //NAaNN
               //0aXN0
               //NNNNN
               //0N0N0
      //B
      {5,4,8},//0N0N0
              //NNbBN
              //0NXb0
              //NNNNN
              //0N0N0

      //C
      {10,7,11},//0N0N0
                //NNNNN
                //0cXN0
                //NCcNN
                //0N0N0

      //D
      {12,8,11},//0N0N0
                //NNNNN
                //0NXd0
                //NNdDN
                //0N0N0
    };
    const std::vector<size_t> preconditions = { //only counts if there is no wall in between
      0,1,          //0A0B0
      0,99,99,99,1, //ANNNB
      99,99,        //0NXN0
      2,99,99,99,3, //CNNND
      2,3           //0C0D0
    };
    const std::vector<size_t> elementsWithPreconditions = {
      0,1,2,6,9,13,14,15
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
      for (const size_t& element : elementsWithPreconditions) {
        size_t areaID = preconditions[element];
        bool fullfilled = true;
        for (const size_t& areaElement : mustFreeAreas[areaID]) {
          fullfilled &= neighbors[areaElement] != maxVal;
        }
        if (!fullfilled)
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