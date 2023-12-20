#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <memory>

namespace RTSPathingLib {
  class RTree2D {
  public:
    RTree2D(const std::vector<std::pair<glm::vec2, size_t>>& bulkInput);
    virtual ~RTree2D();

    std::vector<size_t> boxQuery(const glm::vec2& lowLeftBox, const glm::vec2& upRightBox);
    std::vector<size_t> nearestNeighbour(const glm::vec2 position, size_t amount = 1);

    void remove(size_t index);

  private:
    class RTreeImpl;
    std::unique_ptr<RTreeImpl> p;
  };
}