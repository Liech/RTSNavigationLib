#include "Hex2DVoxelizer.h"

#include <glm/gtx/intersect.hpp>

#include "HexGridUtils.h"
#include "Util/Geometry2D.h"

namespace RTSNavigationLib {
  TopFlatHexGrid<bool> Hex2DVoxelizer::voxelize(const std::vector<glm::dvec2>& polygon, const glm::ivec2& dimension, const glm::dvec2& offset, double scale) {
    TopFlatHexGrid<bool> result;
    result.data.resize(dimension.x * dimension.y);
    result.dimension = dimension;

    for (size_t x = 0; x < dimension.x; x++) {
      glm::dvec2 origin = HexGridUtils::getTopFlatOffset(glm::ivec2(x, -1), offset, scale);
      glm::dvec2 down = origin + glm::dvec2(0, scale * 10 * dimension.y);
      glm::dvec2 dir2 = glm::normalize(down - origin);

      for (size_t i = 1; i < polygon.size(); i++) {
        const glm::dvec2& prev = polygon[i - 1];
        const glm::dvec2& next = polygon[i];
        glm::dvec2 dir = glm::normalize(next - prev);
        double dot = glm::dot(dir, dir2);
        if (std::abs(1 - dot) < 1e-5)
          continue;

        glm::dvec2 intersectionPoint;
        bool intersect = Geometry2D::LineLineIntersect(prev, next, origin, down, intersectionPoint);
        if (intersect) {
          double scaley = scale * (double)std::sqrt(3) * 0.5;
          int start = (int)((intersectionPoint.y - offset.y) / scaley + 0.5);

          for (size_t y = start; y < dimension.y; y++) {
            result.data[x + y * dimension.x] = result.data[x + y * dimension.x] ^ true;
          }
        }
      }
    }

    return result;
  }
}