#pragma once

#include <memory>
#include <vector>
#include <nlohmann/json.hpp>

#include "UnitPlacementBehavior.h"

namespace RTSNavigationLib {
  class FormationShape;

  class Formation {
  public:
    Formation();
    virtual ~Formation();

    size_t getChildrenCount() const;
    Formation& getChild(size_t) const;
    const Formation& getParent() const;
    bool hasParent() const;
    void removeChild(size_t);
    void addChild(std::unique_ptr<Formation>);

    size_t getOwnInterfacePoint() const;
    void   setOwnInterfacePoint(size_t);
    size_t getParentInterfacePoint() const;
    void   setParentInterfacePoint(size_t);
    bool   getOverwriteWidthWithInterfaceWidth() const;
    void   setOverwriteWidthWithInterfaceWidth(bool doIt);
    bool   getRotateWithInterface() const;
    void   setRotateWithInterface(bool v);

    size_t getUnitCategory() const;
    void   setUnitCategory(size_t);
    double getUnitDistributionWeight() const; // if multiple formation nodes have the same category, this can adjust the distribution weighting (higher numbers->more Units)
    void   setUnitDistributionWeight(double v);
    UnitPlacementBehavior getPlacementBehavior() const;
    void   setPlacementBehavior(UnitPlacementBehavior);

    void setShape(std::unique_ptr<FormationShape> shape);
    FormationShape& getShape();
    FormationShape& getShape() const;
    double getRotation() const;
    void setRotation(double rotation);

    void fromJson(const nlohmann::json&);
    nlohmann::json toJson();

  private:
    std::unique_ptr<FormationShape> shape   = nullptr;
    size_t ownInterfacePoint                = 0;
    size_t parentInterfacePoint             = 0;
    bool   overwriteWidthWithInterfaceWidth = false;
    bool   rotateWithInterface              = false;
    double rotation                         = 0.0;
    size_t unitCategory                     = 0;
    double unitDistributionWeight           = 1;
    UnitPlacementBehavior placementBehavior = UnitPlacementBehavior::CenterFirst;

    std::vector<std::unique_ptr<Formation>> children;
    const Formation* parent = nullptr;
  };
}