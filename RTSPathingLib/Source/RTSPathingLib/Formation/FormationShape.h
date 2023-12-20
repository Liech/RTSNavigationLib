#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "ScalingBehavior.h"

class FormationShape {
public:
  FormationShape();
  virtual ~FormationShape();

  virtual std::string getType() const;

  virtual std::vector<glm::vec2> getPolygon() const;
  virtual size_t getNumberOfInterfacePoints() const;
  virtual glm::vec2 getInterfacePoint(size_t number) const;
  virtual float getInterfaceWidth(size_t number) const;

  ScalingBehavior getScalingBehavior() const;
  void setScalingBehavior(const ScalingBehavior& behavior);
  glm::vec2 getBaseSize() const;
  void setBaseSize(const glm::vec2&);

private:
  ScalingBehavior scaling = ScalingBehavior::Isotropic;
  glm::vec2       baseSize = glm::vec2(1,1);
};