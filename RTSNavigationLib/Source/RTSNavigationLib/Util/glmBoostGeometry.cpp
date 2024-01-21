#include "glmBoostGeometry.h"

#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

//https://stackoverflow.com/questions/43303596/finding-resulting-points-using-boost-rtree-in-a-geometry
BOOST_GEOMETRY_REGISTER_POINT_2D(glm::dvec2, double, cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_BOX(RTSNavigationLib::glm2dBox, glm::dvec2, lowLeft, upRight)


namespace RTSNavigationLib {
  glm2dBox::glm2dBox(double x1, double y1, double x2, double y2) :
    lowLeft(x1, y1),
    upRight(x2, y2) {
  }

  glm2dBox::glm2dBox(const glm::dvec2& lowLeft_, const glm::dvec2& upRight_) {
    lowLeft = lowLeft_;
    upRight = upRight_;
  }
}