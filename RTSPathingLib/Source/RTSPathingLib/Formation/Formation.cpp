#include "Formation.h"

#include "FormationShape/FormationShape.h"

namespace RTSPathingLib {
  Formation::Formation(const Formation* parent_) {
    parent = parent_;
  }

  Formation::~Formation() {

  }

  size_t Formation::getChildrenCount() const {
    return children.size();
  }

  Formation& Formation::getChild(size_t i) const {
    return *children[i];
  }

  void Formation::removeChild(size_t number) {
    children.erase(children.begin() + number);
  }

  void Formation::addChild(std::unique_ptr<Formation> child) {
    children.push_back(std::move(child));
  }

  const Formation& Formation::getParent() const {
    return parent;
  }

  size_t Formation::getOwnInterfacePoint() const {
    return ownInterfacePoint;
  }

  void Formation::setOwnInterfacePoint(size_t p) {
    ownInterfacePoint = p;
  }

  size_t Formation::getParentInterfacePoint() const {
    return parentInterfacePoint;
  }

  void Formation::setParentInterfacePoint(size_t p) {
    parentInterfacePoint = p;
  }

  bool Formation::getOverwriteWidthWithInterfaceWidth() const {
    return overwriteWidthWithInterfaceWidth;
  }

  void Formation::setOverwriteWidthWithInterfaceWidth(bool doIt) {
    overwriteWidthWithInterfaceWidth = doIt;
  }

  bool Formation::getRotateWithInterface() const {
    return rotateWithInterface;
  }

  void Formation::setRotateWithInterface(bool v) {
    rotateWithInterface = v;
  }

  bool Formation::getLinkSizeWithParent() const {
    return linkSizeWithParent;
  }

  void Formation::setLinkSizeWithParent(bool v) {
    linkSizeWithParent = v;
  }

  size_t Formation::getUnitCategory() const {
    return unitCategory;
  }

  void Formation::setUnitCategory(size_t category) {
    unitCategory = category;
  }

  void Formation::setShape(std::unique_ptr<FormationShape> shape_) {
    shape = std::move(shape_);
  }

  FormationShape& Formation::getShape() {
    return *shape;
  }
}