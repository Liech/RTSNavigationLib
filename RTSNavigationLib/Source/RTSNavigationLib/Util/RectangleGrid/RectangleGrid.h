#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <functional>

namespace RTSPathingLib {
  template<typename T>
  class RectangleGrid {
  public:
    glm::ivec2 dimension = glm::ivec2(1,1);
    std::vector<T> data;
    glm::ivec2 offset = glm::ivec2(0, 0);
  };

  template<typename T>
  RectangleGrid<T> overlapApply(const RectangleGrid<T>& a, const RectangleGrid<T>& b,std::function<T(const T& a, const T& b)> fun) {
    RectangleGrid<T> result;
    result.data.resize(a.data.size());
    result.dimension = a.dimension;
    result.offset = a.offset;
    result.data = a.data;
    glm::ivec2 a2b = b.offset - a.offset;

    glm::ivec2 aoffset = a.offset;
    glm::ivec2 boffset = b.offset;

    for (int x = std::max(boffset.x, aoffset.x); x < aoffset.x + a.dimension.x && x < boffset.x + b.dimension.x; x++)
      for (int y = std::max(boffset.y, aoffset.y); y < aoffset.y + a.dimension.y && y < boffset.y + b.dimension.y; y++) {
        glm::ivec2 coordForA = glm::ivec2(x, y) - a.offset;
        glm::ivec2 coordForB = glm::ivec2(x, y) - b.offset;
        int coordA = coordForA.x + coordForA.y * a.dimension.x;
        int coordB = coordForB.x + coordForB.y * b.dimension.x;
        result.data[coordA] = fun(a.data[coordA],b.data[coordB]);
      }
    return result;
  }

  template<typename T>
  RectangleGrid<T> operator&(const RectangleGrid<T>& a, const RectangleGrid<T>& b)
  {
    return overlapApply<T>(a, b, [](bool a, bool b) {return a & b; });
  }

  template<typename T>
  RectangleGrid<T> operator|(const RectangleGrid<T>& a, const RectangleGrid<T>& b)
  {
    return overlapApply<T>(a, b, [](bool a, bool b) {return a | b; });
  }

  template<typename T>
  RectangleGrid<T> operator-(const RectangleGrid<T>& a, const RectangleGrid<T>& b)
  {
    return overlapApply<T>(a, b, [](T a, T b) {return a && !b; });
  }
}