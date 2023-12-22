#include "RectangleGridVoxelizer.h"

#include <glm/gtx/intersect.hpp>

#include "Util/Geometry2D.h"

namespace RTSPathingLib {
  RectangleGrid<bool> RectangleGridVoxelizer::voxelize(const std::vector<glm::dvec2>& polygon, const glm::ivec2& dimension, const glm::dvec2& offset, double scale) {
    RectangleGrid<bool> result;
    result.data.resize(dimension.x * dimension.y);
    result.dimension = dimension;
    
    for (size_t x = 0; x < dimension.x; x++) {
      glm::dvec2 origin = offset + glm::dvec2((x+0.5) * scale,-1.0);
      glm::dvec2 down = origin + glm::dvec2(0, scale * 10 * dimension.y);
      glm::dvec2 dir2 = glm::normalize(down - origin);

      int previousPolygonStart = -9999; //make sure if intersections falls on a point of two edges only one is used
      int firstStart = -9999;
      for (size_t i = 0; i < polygon.size(); i++) {
        size_t previous = i-1;
        if (i == 0)
          previous = polygon.size()-1;
        const glm::dvec2& prev = polygon[previous];
        const glm::dvec2& next = polygon[i];
        glm::dvec2 dir = glm::normalize(next - prev);
        double dot = glm::dot(dir, dir2);
        if (std::abs(1 - dot) < 1e-6)
          continue;

        glm::dvec2 intersectionPoint;
        bool intersect = Geometry2D::LineLineIntersect(prev, next, origin, down, intersectionPoint);
        if (intersect) {
          int start = (int)((intersectionPoint.y - offset.y) / scale + 0.5);

          size_t prevprev = i - 2;
          if (i <= 1)
            prevprev = polygon.size() + i - 2;
          const glm::dvec2& prevprevVec = polygon[prevprev];
          float noncolinearity = std::abs(glm::dot(glm::normalize(prev - prevprevVec), glm::normalize(next - prev))); //0==colinear

          if (
            (previousPolygonStart != start) ||//make sure if intersections falls on a point of two edges only one is used, but if they are not too colinear its allowed
            (i==polygon.size()-1 && firstStart == start) || noncolinearity < 0.7) { 
            previousPolygonStart = start;
            if (i == 0)
              firstStart = start;

            for (size_t y = start; y < dimension.y; y++) {
              result.data[x + y * dimension.x] = result.data[x + y * dimension.x] ^ true;
            }
          }
          else
            previousPolygonStart = -1;
        }
        else
          previousPolygonStart = -1;
      }
    }
    result.offset = offset;
    return result;
  }
}