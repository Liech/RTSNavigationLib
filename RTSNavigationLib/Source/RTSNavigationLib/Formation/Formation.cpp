#include "Formation.h"

#include "FormationShape/FormationShape.h"
#include "FormationShape/FormationShapeFactory.h"
#include "FormationShape/RectangleFormationShape.h"

namespace RTSNavigationLib
{
    Formation::Formation()
    {
        shape = std::make_unique<RectangleFormationShape>();
    }

    Formation::~Formation() {}

    size_t Formation::getChildrenCount() const
    {
        return children.size();
    }

    Formation& Formation::getChild(size_t i) const
    {
        return *children[i];
    }

    void Formation::removeChild(size_t number)
    {
        children.erase(children.begin() + number);
    }

    void Formation::addChild(std::unique_ptr<Formation> child)
    {
        child->parent = this;
        children.push_back(std::move(child));
    }

    const Formation& Formation::getParent() const
    {
        return *parent;
    }

    bool Formation::hasParent() const
    {
        return parent != nullptr;
    }

    size_t Formation::getOwnInterfacePoint() const
    {
        return ownInterfacePoint;
    }

    void Formation::setOwnInterfacePoint(size_t p)
    {
        ownInterfacePoint = p;
    }

    size_t Formation::getParentInterfacePoint() const
    {
        return parentInterfacePoint;
    }

    void Formation::setParentInterfacePoint(size_t p)
    {
        parentInterfacePoint = p;
    }

    bool Formation::getOverwriteWidthWithInterfaceWidth() const
    {
        return overwriteWidthWithInterfaceWidth;
    }

    void Formation::setOverwriteWidthWithInterfaceWidth(bool doIt)
    {
        overwriteWidthWithInterfaceWidth = doIt;
    }

    bool Formation::getRotateWithInterface() const
    {
        return rotateWithInterface;
    }

    void Formation::setRotateWithInterface(bool v)
    {
        rotateWithInterface = v;
    }

    std::vector<size_t> Formation::getUnitCategories() const
    {
        return unitCategories;
    }

    void Formation::setUnitCategories(const std::vector<size_t>& category)
    {
        unitCategories = category;
    }

    double Formation::getUnitDistributionWeight() const
    {
        return unitDistributionWeight;
    }

    void Formation::setUnitDistributionWeight(double v)
    {
        unitDistributionWeight = v;
    }

    void Formation::setShape(std::unique_ptr<FormationShape> shape_)
    {
        shape = std::move(shape_);
    }

    FormationShape& Formation::getShape()
    {
        return *shape;
    }

    FormationShape& Formation::getShape() const
    {
        return *shape;
    }

    double Formation::getRotation() const
    {
        return rotation;
    }

    void Formation::setRotation(double rotation_)
    {
        rotation = rotation_;
    }

    UnitPlacementBehavior Formation::getPlacementBehavior() const
    {
        return placementBehavior;
    }

    void Formation::setPlacementBehavior(UnitPlacementBehavior value)
    {
        placementBehavior = value;
    }

    UnitPlacementBehavior Formation::getCutBehavior() const
    {
        return cutBehavior;
    }

    void Formation::setCutBehavior(UnitPlacementBehavior value)
    {
        cutBehavior = value;
    }

    bool Formation::getCenterShift() const
    {
        return centerShift;
    }

    void Formation::setCenterShift(bool active)
    {
        centerShift = active;
    }
    bool Formation::getIsRemainingUnitSink() const
    {
        return remainingUnitsSink;
    }

    void Formation::setIsRemainingUnitSink(bool active)
    {
        remainingUnitsSink = active;
    }

    void Formation::fromJson(const nlohmann::json& input)
    {
        shape = FormationShapeFactory::make(input["Shape"]);

        ownInterfacePoint                = input["OwnInterfacePoint"];
        parentInterfacePoint             = input["ParentInterfacePoint"];
        overwriteWidthWithInterfaceWidth = input["OverwriteWidthWithInterfaceWidth"];
        rotateWithInterface              = input["RotateWithInterface"];
        rotation                         = input["Rotation"];
        unitCategories                   = std::vector<size_t>(input["UnitCategory"].begin(), input["UnitCategory"].end());
        unitDistributionWeight           = input["UnitDistributionWeight"];
        placementBehavior                = String2UnitPlacementBehavior(input["PlacementBehavior"]);
        centerShift                      = input["CenterShift"];
        remainingUnitsSink               = input["RemainingUnitSink"];

        children.clear();
        for (auto& child : input["Children"])
        {
            std::unique_ptr<Formation> formation = std::make_unique<Formation>();
            formation->fromJson(child);
            children.push_back(std::move(formation));
        }
    }

    nlohmann::json Formation::toJson()
    {
        nlohmann::json result;
        result["Shape"] = shape->toJson();

        result["OwnInterfacePoint"]                = ownInterfacePoint;
        result["ParentInterfacePoint"]             = parentInterfacePoint;
        result["OverwriteWidthWithInterfaceWidth"] = overwriteWidthWithInterfaceWidth;
        result["RotateWithInterface"]              = rotateWithInterface;
        result["Rotation"]                         = rotation;
        result["UnitCategory"]                     = unitCategories;
        result["UnitDistributionWeight"]           = unitDistributionWeight;
        result["PlacementBehavior"]                = UnitPlacementBehavior2String(placementBehavior);
        result["CenterShift"]                      = centerShift;
        result["RemainingUnitSink"]                = remainingUnitsSink;

        result["Children"] = nlohmann::json::array();
        for (auto& child : children)
        {
            result["Children"].push_back(child->toJson());
        }
        return result;
    }
}