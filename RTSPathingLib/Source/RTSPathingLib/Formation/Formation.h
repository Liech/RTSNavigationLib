#pragma once

#include <memory>
#include <vector>

class FormationShape;

class Formation {
public:
  Formation(const Formation* parent);
  virtual ~Formation();

  size_t getChildrenCount() const;
  Formation& getChild(size_t) const;
  const Formation& getParent() const;
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

  void setShape(std::unique_ptr<FormationShape> shape);
  FormationShape& getShape();

private:
  std::unique_ptr<FormationShape> shape;
  size_t ownInterfacePoint    = 0;
  size_t parentInterfacePoint = 0;
  bool   overwriteWidthWithInterfaceWidth = false;
  bool   rotateWithInterface = false;
  bool   linkSizeWithParent = false;
  
  size_t unitCategory = 0;

  std::vector<std::unique_ptr<Formation>> children;
  const Formation* parent = nullptr;
};