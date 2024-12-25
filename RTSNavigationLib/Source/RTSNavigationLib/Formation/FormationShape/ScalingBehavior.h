#pragma once

#include <string>

namespace RTSNavigationLib
{
    enum class ScalingBehavior : unsigned char
    {
        PureX     = 0,
        PureY     = 1,
        Isotropic = 2,
        X75Y25    = 3,
        X25Y75    = 4
    };

    ScalingBehavior String2ScalingBehavior(const std::string&);
    std::string     ScalingBehavior2String(ScalingBehavior);
}