#include "ScalingBehavior.h"

namespace RTSNavigationLib
{

    ScalingBehavior String2ScalingBehavior(const std::string& input)
    {
        if (input == "Isotropic")
            return ScalingBehavior::Isotropic;
        else if (input == "PureX")
            return ScalingBehavior::PureX;
        else if (input == "PureY")
            return ScalingBehavior::PureY;
        else if (input == "PureX")
            return ScalingBehavior::X25Y75;
        else if (input == "X25Y75")
            return ScalingBehavior::X75Y25;
        return ScalingBehavior::Isotropic;
    }

    std::string ScalingBehavior2String(ScalingBehavior input)
    {
        switch (input)
        {
            case ScalingBehavior::PureX:
                return "PureX";
            case ScalingBehavior::PureY:
                return "PureY";
            case ScalingBehavior::X75Y25:
                return "X75Y25";
            case ScalingBehavior::X25Y75:
                return "X25Y75";
            case ScalingBehavior::Isotropic:
            default:
                return "Isotropic";
        }
    }
}