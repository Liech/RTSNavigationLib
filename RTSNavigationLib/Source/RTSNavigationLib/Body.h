#pragma once

#include <glm/glm.hpp>
#include <tuple>

namespace RTSNavigationLib
{
    struct Body
    {
        Body(size_t category_, size_t size_ = 1)
        {
            category = category_;
            size     = size_;
        }

        Body()
        {
            category = 0;
            size     = 1;
        }

        size_t     category;
        size_t     size;

        const bool operator<(const Body& r) const
        {
            return std::tie(size, category) < std::tie(r.size, r.category);
        }
    };
}