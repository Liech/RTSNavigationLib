#pragma once

#include "FormationShape.h"

class ArcFormationShape : public FormationShape {
public:
  ArcFormationShape();
  virtual ~ArcFormationShape();

  virtual std::string getType() const override;

  virtual std::vector<glm::vec2> getPolygon() const        override;
  virtual size_t getNumberOfInterfacePoints() const        override;
  virtual glm::vec2 getInterfacePoint(size_t number) const override; //center, border+1/36, border+2/36,...
  virtual float getInterfaceWidth(size_t number) const;

  float getArcAngle() const;
  void setArcAngle(float valueRadian);

private:
  float arcAngleRadian = 0.0f; // for e.g half circles. 0 means full circle, pi means half circle, 2pi means nothing

  const size_t numberPolygons = 36;
};