#pragma once

#include <glm/vec2.hpp>
#include <vector>

namespace RTSPathingLib {
  template<typename T>
  class RectangleGrid {
  public:
    glm::ivec2 dimension = glm::ivec2(1,1);
    std::vector<T> data;
    glm::dvec2 offset = glm::dvec2(0, 0);
  };

  template<typename T>
  RectangleGrid<T> operator&(const RectangleGrid<T>& a, const RectangleGrid<T>& b)
  {
    RectangleGrid<T> result;
    result.data.resize(a.data.size());
    result.dimension = a.dimension;
    for (size_t i = 0; i < a.data.size(); i++)
      result.data[i] = a.data[i] & b.data[i];
    return result;
  }
  template<typename T>
  RectangleGrid<T> operator|(const RectangleGrid<T>& a, const RectangleGrid<T>& b)
  {
    RectangleGrid<T> result;
    result.data.resize(a.data.size());
    result.dimension = a.dimension;
    for (size_t i = 0; i < a.data.size(); i++)
      result.data[i] = a.data[i] | b.data[i];
    return result;
  }
  template<typename T>
  RectangleGrid<T> operator-(const RectangleGrid<T>& a, const RectangleGrid<T>& b)
  {
    RectangleGrid<T> result;
    result.data.resize(a.data.size());
    result.dimension = a.dimension;
    for (size_t i = 0; i < a.data.size(); i++) {
      bool aV = a.data[i];
      bool bV = b.data[i];
      result.data[i] = aV&&!bV;
    }
    return result;
  }
}