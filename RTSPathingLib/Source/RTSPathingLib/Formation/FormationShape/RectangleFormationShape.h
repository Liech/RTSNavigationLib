#pragma once

#include "FormationShape.h"

class RectangleFormationShape : public FormationShape {
public:
  RectangleFormationShape();
  virtual ~RectangleFormationShape();  
  
  virtual std::string getType() const override;

  virtual std::vector<glm::vec2> getPolygon() const        override;
  virtual size_t getNumberOfInterfacePoints() const        override; 
  virtual glm::vec2 getInterfacePoint(size_t number) const override; //center, edge0 start, edge0 center, edge1 start,... edge3 center
  virtual float getInterfaceWidth(size_t number) const;


private:
};