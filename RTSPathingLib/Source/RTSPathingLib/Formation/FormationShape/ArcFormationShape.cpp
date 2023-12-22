#include "ArcFormationShape.h"

#include <glm/ext/scalar_constants.hpp>

namespace RTSPathingLib {
  ArcFormationShape::ArcFormationShape() {

  }

  ArcFormationShape::~ArcFormationShape() {

  }

  std::string ArcFormationShape::getType() const {
    return "Arc";
  }

  size_t ArcFormationShape::getNumberOfInterfacePoints() const {
    return numberPolygons + 1;
  }

  glm::dvec2 ArcFormationShape::getInterfacePoint(size_t number) const {
    if (number == 0)
      return glm::dvec2(0, 0);
    size_t edge = (number - 1) % numberPolygons;
    auto poly = getPolygon();
    glm::dvec2 result = poly[edge] + (poly[(edge + 1) % numberPolygons] - poly[edge]) / 2.0;
    return result;
  }

  std::vector<glm::dvec2> ArcFormationShape::getPolygon() const {
    std::vector<glm::dvec2> result;
    glm::dvec2 size = getBaseSize();

    double from = arcAngleRadian / 2;
    double till = glm::pi<double>() * 2 - from;

    for (size_t i = 0; i < numberPolygons; i++) {
      double perc = (double)i / (double)(numberPolygons-1);
      double angle = from + (till - from) * perc;
      glm::dvec2 pos = glm::dvec2(std::sin(angle) * size.x * 0.5, std::cos(angle) * size.y * 0.5);
      result.push_back(pos);
    }
    if (arcAngleRadian != 0) {
      glm::dvec2 pos = glm::dvec2(std::sin(0) * size.x * 0.01, std::cos(0) * size.y * 0.01);
      result.push_back(pos);
    }
    else {
      glm::dvec2 pos = glm::dvec2(std::sin(0) * size.x * 0.5, std::cos(0) * size.y * 0.5);
      result.push_back(pos);
    }


    return result;
  }

  double ArcFormationShape::getInterfaceWidth(size_t number) const {
    if (number == 0)
      return 0;
    size_t edge = (number - 1) % numberPolygons;
    auto poly = getPolygon();
    double result = glm::distance(poly[edge], poly[(edge + 1) % numberPolygons]);
    return result;
  }

  double ArcFormationShape::getArcAngle() const {
    return arcAngleRadian;
  }

  void ArcFormationShape::setArcAngle(double valueRadian) {
    arcAngleRadian = valueRadian;
  }

  glm::dvec2 ArcFormationShape::getInterfaceNormal(size_t number) const {
    if (number == 0)
      return glm::dvec2(0, 1);
    size_t edge = (number - 1) % numberPolygons;
    auto poly = getPolygon();
    glm::dvec2 result = glm::normalize(poly[(edge + 1) % numberPolygons] - poly[edge]);
    result = glm::dvec2(-result.y, result.x);
    if (glm::length(result) < 1e-5)
      return glm::dvec2(0, 1);
    return result;
  }
}