#include "FormationShape.h"

namespace RTSNavigationLib
{
    FormationShape::FormationShape() {}

    FormationShape::~FormationShape() {}

    std::string FormationShape::getType() const
    {
        return "Base";
    }

    size_t FormationShape::getNumberOfInterfacePoints() const
    {
        return 1;
    }

    glm::dvec2 FormationShape::getInterfacePoint(size_t number) const
    {
        return glm::dvec2(0, 0);
    }

    glm::dvec2 FormationShape::getInterfaceNormal(size_t number) const
    {
        return glm::dvec2(0, 1);
    }

    std::vector<glm::dvec2> FormationShape::getPolygon() const
    {
        return {};
    }

    double FormationShape::getInterfaceWidth(size_t, const glm::dvec2& scale) const
    {
        return 0;
    }

    ScalingBehavior FormationShape::getScalingBehavior() const
    {
        return scaling;
    }

    void FormationShape::setScalingBehavior(const ScalingBehavior& behavior)
    {
        scaling = behavior;
    }

    glm::dvec2 FormationShape::getBaseSize() const
    {
        return baseSize;
    }

    void FormationShape::setBaseSize(const glm::dvec2& size)
    {
        baseSize = size;
    }

    double FormationShape::getHollow() const
    {
        return hollow;
    }

    void FormationShape::setHollow(double value)
    {
        hollow = value;
    }

    void FormationShape::fromJson(const nlohmann::json& input)
    {
        baseSize = glm::dvec2(input["Size"][0], input["Size"][1]);
        scaling  = String2ScalingBehavior(input["Scaling"]);
        hollow   = input["Hollow"];
    }

    nlohmann::json FormationShape::toJson()
    {
        nlohmann::json result;
        result["Size"]    = std::array<double, 2>{ baseSize[0], baseSize[0] };
        result["Scaling"] = ScalingBehavior2String(scaling);
        result["Hollow"]  = hollow;
        return result;
    }
}