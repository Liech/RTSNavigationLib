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
    size_t getParentInterfacePoint() const;//unimplemented
    void   setParentInterfacePoint(size_t);
    bool   getOverwriteWidthWithInterfaceWidth() const;//unimplemented
    void   setOverwriteWidthWithInterfaceWidth(bool doIt);
    bool   getRotateWithInterface() const;//unimplemented
    void   setRotateWithInterface(bool v);
    bool   getLinkSizeWithParent() const;//unimplemented
    void   setLinkSizeWithParent(bool v);

    size_t getUnitCategory() const;
    void   setUnitCategory(size_t);
    double getUnitDistributionWeight() const; //untested // if multiple formation nodes have the same category, this can adjust the distribution weighting (higher numbers->more Units)
    void   setUnitDistributionWeight(double v);
    double getUnitPadding() const; //unimplemented //how much the units are appart from eachother
    void   setUnitPadding(double padding);

    void setShape(std::unique_ptr<FormationShape> shape);
    FormationShape& getShape();
    FormationShape& getShape() const;
    double getRotation() const;
    void setRotation(double rotation);

  private:
    std::unique_ptr<FormationShape> shape   = nullptr;
    size_t ownInterfacePoint                = 0;
    size_t parentInterfacePoint             = 0;
    bool   overwriteWidthWithInterfaceWidth = false;
    bool   rotateWithInterface              = false;
    bool   linkSizeWithParent               = false;
    double unitPadding                      = 1.1;
    double rotation                         = 0.0;

    size_t unitCategory = 0;
    double  unitDistributionWeight = 1;

    std::vector<std::unique_ptr<Formation>> children;
    const Formation* parent = nullptr;
  };
}