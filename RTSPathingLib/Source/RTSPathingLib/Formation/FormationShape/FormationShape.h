#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "ScalingBehavior.h"

namespace RTSPathingLib {
  class FormationShape {
  public:
    FormationShape();
    virtual ~FormationShape();

    virtual std::string getType() const;

    virtual std::vector<glm::dvec2> getPolygon() const;
    virtual size_t getNumberOfInterfacePoints() const;
    virtual glm::dvec2 getInterfacePoint(size_t number) const;
    virtual glm::dvec2 getInterfaceNormal(size_t number) const;
    virtual double     getInterfaceWidth(size_t number, const glm::dvec2& scale) const;

    ScalingBehavior getScalingBehavior() const;
    void setScalingBehavior(const ScalingBehavior& behavior);
    glm::dvec2 getBaseSize() const;
    void setBaseSize(const glm::dvec2&);

  private:
    ScalingBehavior scaling = ScalingBehavior::Isotropic;
    glm::dvec2       baseSize = glm::dvec2(1, 1);
  };
}