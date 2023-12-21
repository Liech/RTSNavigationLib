#pragma once

#include <memory>
#include <vector>

namespace RTSPathingLib {
  class FormationShape;

  class Formation {
  public:
    Formation(const Formation* parent);
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
    bool   getLinkSizeWithParent() const;
    void   setLinkSizeWithParent(bool v);

    size_t getUnitCategory() const;
    void   setUnitCategory(size_t);
    float  getUnitDistributionWeight() const; // if multiple formation nodes have the same category, this can adjust the distribution weighting (higher numbers->more Units)
    void   setUnitDistributionWeight(float v);
    float  getUnitPadding() const; //how much the units are appart from eachother
    void   setUnitPadding(float padding);

    void setShape(std::unique_ptr<FormationShape> shape);
    FormationShape& getShape();
    FormationShape& getShape() const;

  private:
    std::unique_ptr<FormationShape> shape   = nullptr;
    size_t ownInterfacePoint                = 0;
    size_t parentInterfacePoint             = 0;
    bool   overwriteWidthWithInterfaceWidth = false;
    bool   rotateWithInterface              = false;
    bool   linkSizeWithParent               = false;
    float  unitPadding                      = 1.1f;

    size_t unitCategory = 0;
    float  unitDistributionWeight = 1;

    std::vector<std::unique_ptr<Formation>> children;
    const Formation* parent = nullptr;
  };
}