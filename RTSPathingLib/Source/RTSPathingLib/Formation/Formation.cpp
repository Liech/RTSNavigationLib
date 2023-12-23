#include "Formation.h"

#include "FormationShape/FormationShape.h"
#include "FormationShape/RectangleFormationShape.h"

namespace RTSPathingLib {
  Formation::Formation() {
    shape = std::make_unique<RectangleFormationShape>();
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
    child->parent = this;
    children.push_back(std::move(child));
  }

  const Formation& Formation::getParent() const {
    return *parent;
  }
  
  bool Formation::hasParent() const {
    return parent != nullptr;
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

  double Formation::getUnitDistributionWeight() const {
    return unitDistributionWeight;
  }

  void Formation::setUnitDistributionWeight(double v) {
    unitDistributionWeight = v;
  }

  void Formation::setShape(std::unique_ptr<FormationShape> shape_) {
    shape = std::move(shape_);
  }

  FormationShape& Formation::getShape() {
    return *shape;
  }

  FormationShape& Formation::getShape() const {
    return *shape;
  }

  double Formation::getUnitPadding() const {
    return unitPadding;
  }

  void Formation::setUnitPadding(double padding) {
    unitPadding = padding;
  }

  double Formation::getRotation() const {
    return rotation;
  }

  void Formation::setRotation(double rotation_) {
    rotation = rotation_;
  }
}