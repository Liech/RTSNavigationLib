#include "Hex2DVoxelizer.h"

#include <glm/gtx/intersect.hpp>

#include "HexGridUtils.h"

//https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool Hex2DVoxelizer::LineLineIntersect(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2& i) //Output 
{
  float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
  s10_x = p1.x - p0.x;
  s10_y = p1.y - p0.y;
  s32_x = p3.x - p2.x;
  s32_y = p3.y - p2.y;

  denom = s10_x * s32_y - s32_x * s10_y;
  if (denom == 0)
    return false; // Collinear
  bool denomPositive = denom > 0;

  s02_x = p0.x - p2.x;
  s02_y = p0.y - p2.y;
  s_numer = s10_x * s02_y - s10_y * s02_x;
  if ((s_numer < 1e-5) == denomPositive)
    return false; // No collision

  t_numer = s32_x * s02_y - s32_y * s02_x;
  if ((t_numer < 1e-5) == denomPositive)
    return false; // No collision

  if (((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
    return false; // No collision
  // Collision detected
  t = t_numer / denom;
  if (i.x != NULL)
    i.x = p0.x + (t * s10_x);
  if (i.y != NULL)
    i.y = p0.y + (t * s10_y);

  return true;
}

TopFlatHexGrid<bool> Hex2DVoxelizer::voxelize(const std::vector<glm::vec2>& polygon, const glm::ivec2& dimension, const glm::vec2& offset, float scale) {
  TopFlatHexGrid<bool> result;
  result.data.resize(dimension.x * dimension.y);
  result.dimension = dimension;

  for (size_t x = 0; x < dimension.x; x++) {
    glm::vec2 origin = HexGridUtils::getTopFlatOffset(glm::ivec2(x,-1),offset,scale);
    glm::vec2 down   = origin + glm::vec2(0, scale * 10 * dimension.y);
    glm::vec2 dir2 = glm::normalize(down - origin);

    for (size_t i = 1; i < polygon.size(); i++) {
      const glm::vec2& prev = polygon[i-1];
      const glm::vec2& next = polygon[i];
      glm::vec2 dir = glm::normalize(next - prev);
      float dot = glm::dot(dir, dir2);
      if (std::abs(1-dot) < 1e-5)
        continue;

      glm::vec2 intersectionPoint;
      bool intersect = LineLineIntersect(prev,next,origin,down,intersectionPoint);
      if (intersect) {
        float scaley = scale * std::sqrt(3) * 0.5f;
        int start = ((intersectionPoint.y - offset.y) / scaley + 0.5f);

        for (size_t y = start; y < dimension.y; y++) {
          result.data[x + y * dimension.x] = result.data[x + y * dimension.x] ^ true;
        }
        
      }
    }
  }


  return result;
}