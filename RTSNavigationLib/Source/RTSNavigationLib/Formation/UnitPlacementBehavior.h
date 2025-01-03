#pragma once

#include <string>

namespace RTSNavigationLib
{
    enum class UnitPlacementBehavior : unsigned char
    {
        CenterFirst      = 0,
        OuterFirst       = 1,
        DistributeEvenly = 2,
        FrontFirst       = 3,
        RearFirst        = 4
    };

    std::string           UnitPlacementBehavior2String(const UnitPlacementBehavior&);
    UnitPlacementBehavior String2UnitPlacementBehavior(const std::string&);
}