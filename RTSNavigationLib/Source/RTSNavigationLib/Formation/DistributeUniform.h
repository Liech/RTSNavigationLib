#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RTSNavigationLib
{
    // Comparable way of solving the assignment problem: building two kd trees, that are on closer inspection not alternating between x and y, but checking main axis
    // Seperate in two piles along the main axis, put half in left, half in right pile, if only one left, place in center

    class DistributeUniform
    {
      public:
        static std::vector<glm::ivec2> distribute(const std::vector<glm::ivec2>& places, size_t amountToPlace);

      private:
        static std::vector<glm::ivec2> placeRecursive(std::vector<glm::ivec2>& places, size_t amountToPlace);
        static bool                    findMainAxis(const std::vector<glm::ivec2>& places);
        static glm::ivec2              placeLast(const std::vector<glm::ivec2>& places);
        static glm::dvec2              getCenter(const std::vector<glm::ivec2>& places);
    };
}