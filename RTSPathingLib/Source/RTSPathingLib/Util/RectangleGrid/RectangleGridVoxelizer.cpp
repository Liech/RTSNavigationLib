#include "RectangleGridVoxelizer.h"

#include <glm/gtx/intersect.hpp>

#include "Util/Geometry2D.h"

namespace RTSPathingLib {
  RectangleGrid<bool> RectangleGridVoxelizer::voxelize(const std::vector<glm::vec2>& polygon, const glm::ivec2& dimension, const glm::vec2& offset, float scale) {
    RectangleGrid<bool> result;
    result.data.resize(dimension.x * dimension.y);
    result.dimension = dimension;

    for (size_t x = 0; x < dimension.x; x++) {
      glm::vec2 origin = offset + glm::vec2((x+0.5f) * scale,-1.0f);
      glm::vec2 down = origin + glm::vec2(0, scale * 10 * dimension.y);
      glm::vec2 dir2 = glm::normalize(down - origin);

      for (size_t i = 1; i < polygon.size(); i++) {
        const glm::vec2& prev = polygon[i - 1];
        const glm::vec2& next = polygon[i];
        glm::vec2 dir = glm::normalize(next - prev);
        float dot = glm::dot(dir, dir2);
        if (std::abs(1 - dot) < 1e-5)
          continue;

        glm::vec2 intersectionPoint;
        bool intersect = Geometry2D::LineLineIntersect(prev, next, origin, down, intersectionPoint);
        if (intersect) {
          int start = ((intersectionPoint.y - offset.y) / scale + 0.5f);

          for (size_t y = start; y < dimension.y; y++) {
            result.data[x + y * dimension.x] = result.data[x + y * dimension.x] ^ true;
          }
        }
      }
    }

    return result;
  }
}