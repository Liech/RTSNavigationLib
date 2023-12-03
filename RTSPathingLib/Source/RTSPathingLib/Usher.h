#pragma once

#include <vector>

namespace RTSPathingLib {
  class Body;

  class Usher {
  public:
    Usher();

    static std::vector<size_t> assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places);
  };
}