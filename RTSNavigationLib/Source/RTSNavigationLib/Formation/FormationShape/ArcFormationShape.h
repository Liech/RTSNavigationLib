#pragma once

#include "FormationShape.h"

namespace RTSPathingLib {
  class ArcFormationShape : public FormationShape {
  public:
    ArcFormationShape();
    virtual ~ArcFormationShape();

    virtual std::string getType() const override;

    virtual std::vector<glm::dvec2> getPolygon() const        override;
    virtual size_t getNumberOfInterfacePoints() const        override;
    virtual glm::dvec2 getInterfacePoint(size_t number) const override; //center, border+1/36, border+2/36,...
    virtual glm::dvec2 getInterfaceNormal(size_t number) const override;
    virtual double getInterfaceWidth(size_t number, const glm::dvec2& scale) const;

    virtual void fromJson(const nlohmann::json&) override;
    virtual nlohmann::json toJson() override;

    double getArcAngle() const;
    void setArcAngle(double valueRadian);

  private:
    double arcAngleRadian = 0.0; // for e.g half circles. 0 means full circle, pi means half circle, 2pi means nothing

    const size_t numberPolygons = 36;
  };
}