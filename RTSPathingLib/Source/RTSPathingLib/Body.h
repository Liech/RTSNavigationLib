#pragma once

#include <glm/glm.hpp>

namespace RTSPathingLib {
  struct Body {
    glm::vec2 position   ;
    size_t    blueprintID;
  };
}