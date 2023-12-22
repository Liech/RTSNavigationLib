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
    i.x = p0.x + (t * s10_x);
    i.y = p0.y + (t * s10_y);

    return true;
  }
  //https://www.geeksforgeeks.org/find-the-centroid-of-a-non-self-intersecting-closed-polygon/
	glm::dvec2 Geometry2D::findCentroid(const std::vector<glm::dvec2>& v)
	{
		glm::dvec2 ans = glm::dvec2(0,0);

		int n = v.size();
		double signedArea = 0;

		// For all vertices
		for (int i = 0; i < v.size(); i++) {

			double x0 = v[i].x, y0 = v[i].y;
			double x1 = v[(i + 1) % n].x, y1 =
				v[(i + 1) % n].y;

			// Calculate value of A
			// using shoelace formula
			double A = (x0 * y1) - (x1 * y0);
			signedArea += A;

			// Calculating coordinates of
			// centroid of polygon
			ans.x += (x0 + x1) * A;
			ans.y += (y0 + y1) * A;
		}

		signedArea *= 0.5;
		ans.x = (ans.x) / (6 * signedArea);
		ans.y = (ans.y) / (6 * signedArea);

		return ans;
	}
}