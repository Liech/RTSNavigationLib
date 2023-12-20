#pragma once

#include "FormationShape.h"

class TriangleFormationShape : public FormationShape {
public:
  TriangleFormationShape();
  virtual ~TriangleFormationShape();
  virtual std::string getType() const override;

  virtual std::vector<glm::vec2> getPolygon() const        override;
  virtual size_t getNumberOfInterfacePoints() const        override;
  virtual glm::vec2 getInterfacePoint(size_t number) const override; //center, edge0 start, edge0 center, edge1 start,... edge2 center
  virtual glm::vec2 getInterfaceNormal(size_t number) const override;
  virtual float getInterfaceWidth(size_t number) const;

private:
  int  layoutEdge     = 0; //-1 for centered
};