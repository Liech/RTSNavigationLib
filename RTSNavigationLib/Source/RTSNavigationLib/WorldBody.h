#pragma once

#include <glm/glm.hpp>
#include <tuple>

namespace RTSNavigationLib
{
    struct WorldBody
    {
        WorldBody(const glm::dvec2& pos, size_t category_, size_t size_ = 1)
        {
            position = pos;
            category = category_;
            size     = size_;
        }

        WorldBody()
        {
            position = glm::dvec2(0, 0);
            category = 0;
            size     = 1;
        }

        glm::dvec2 position;
        size_t     category;
        size_t     size;

        const bool operator<(const WorldBody& r) const
        {
            return std::tie(size, category, position.x, position.y) < std::tie(r.size, r.category, r.position.x, r.position.y);
        }
    };
}