#pragma once

#include <glm/glm.hpp>

namespace RTSPathingLib {
  struct Body {
    Body(const glm::vec2& pos, size_t category_, size_t size_ = 1) {
      position = pos;
      category = category_;
      size     = size_;
    }

    Body() {
      position = glm::vec2(0, 0);
      category = 0;
      size     = 1;
    }

    glm::vec2 position;
    size_t    category;
    size_t    size    ;
  };
}