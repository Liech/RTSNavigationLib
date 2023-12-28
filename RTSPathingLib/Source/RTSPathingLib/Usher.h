#pragma once

#include <vector>
#include <memory>


namespace RTSPathingLib {
  struct Body;
  class RTree2D;

  class Usher {
  public:
    Usher();
    static void assignPlaces2();
    static std::vector<size_t> assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places);

    static void visualize(const std::vector<size_t>& usherResult, const std::vector<Body>& units, const std::vector<Body>& places);
  private:
    struct ticket {
      size_t place;
      size_t unit;
      double distance;
    };
    static std::vector<ticket> firstEstimate(const std::vector<Body>& units, const std::vector<Body>& places, RTree2D& tree);
    static std::unique_ptr<RTree2D> buildTree(const std::vector<Body>& places);

  };
}