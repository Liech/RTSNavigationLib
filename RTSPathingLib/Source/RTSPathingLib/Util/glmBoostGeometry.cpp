#include "glmBoostGeometry.h"

#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

//https://stackoverflow.com/questions/43303596/finding-resulting-points-using-boost-rtree-in-a-geometry
BOOST_GEOMETRY_REGISTER_POINT_2D(glm::vec2, float, cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_BOX(glm2dBox, glm::vec2, lowLeft, upRight)


glm2dBox::glm2dBox(float x1, float y1, float x2, float y2) :
  lowLeft(x1, y1),
  upRight(x2, y2) {
}

glm2dBox::glm2dBox(const glm::vec2& lowLeft_, const glm::vec2& upRight_) {
  lowLeft = lowLeft_;
  upRight = upRight_;
}