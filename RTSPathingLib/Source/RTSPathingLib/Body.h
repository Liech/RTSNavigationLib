#pragma once

#include <glm/glm.hpp>

namespace RTSPathingLib {
  struct Body {
    Body(const glm::vec2& pos, size_t id) {
      position    = pos;
      blueprintID = id;
    }

    Body() {
      position    = glm::vec2(0, 0);
      blueprintID = 0;
    }

    glm::vec2 position   ;
    size_t    blueprintID;
  };
}