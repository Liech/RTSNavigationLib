#pragma once

#include <vector>
#include <memory>


namespace RTSNavigationLib {
  struct Body;
  class RTree2D;

  class Usher {
  public:
    Usher();
    static std::vector<size_t> assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places);
    static std::vector<size_t> assignPlaces2KD(const std::vector<Body>& units, const std::vector<Body>& places);
    static std::vector<size_t> assignPlacesMCF(const std::vector<Body>& units, const std::vector<Body>& places);

    static void visualize(const std::vector<size_t>& usherResult, const std::vector<Body>& units, const std::vector<Body>& places);
  private:

  };
}