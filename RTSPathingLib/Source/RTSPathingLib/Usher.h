#pragma once

#include <vector>
#include <memory>

class RTree2D;

namespace RTSPathingLib {
  struct Body;

  class Usher {
  public:
    Usher();

    static std::vector<size_t> assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places);

  private:
    struct ticket {
      size_t place;
      size_t unit;
      float distance;
    };
    static std::vector<ticket> firstEstimate(const std::vector<Body>& units, const std::vector<Body>& places, RTree2D& tree);
    static std::unique_ptr<RTree2D> buildTree(const std::vector<Body>& places);

  };
}