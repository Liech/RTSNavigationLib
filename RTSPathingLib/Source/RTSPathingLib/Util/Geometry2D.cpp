#include "Geometry2D.h"

namespace RTSPathingLib {
  //https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
  bool Geometry2D::LineLineIntersect(glm::dvec2 p0, glm::dvec2 p1, glm::dvec2 p2, glm::dvec2 p3, glm::dvec2& i) //Output 
  {
    double s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
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
    if ((s_numer < 1e-16) == denomPositive)
      return false; // No collision

    t_numer = s32_x * s02_y - s32_y * s02_x;
    if ((t_numer < 1e-16) == denomPositive)
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
}