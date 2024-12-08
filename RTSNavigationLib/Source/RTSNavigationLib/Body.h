#pragma once

#include <glm/glm.hpp>

namespace RTSNavigationLib
{
    struct Body
    {
        Body(const glm::dvec2& pos, size_t category_, size_t size_ = 1, size_t id_ = 0)
        {
            position = pos;
            category = category_;
            size     = size_;
            id       = id_;
        }

        Body()
        {
            position = glm::dvec2(0, 0);
            category = 0;
            size     = 1;
            id       = 0;
        }

        glm::dvec2 position;
        size_t     category;
        size_t     size;
        size_t     id = 0;
    };
}