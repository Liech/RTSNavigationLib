#include "Usher.h"

#include "Body.h"

namespace RTSPathingLib {
  Usher::Usher() {

  }

  std::vector<size_t> Usher::assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places) {
    std::vector<size_t> result;
    result.resize(units.size());

    assert(units.size() == places.size());

    //just assign naive as ordered
    for (size_t i = 0; i < units.size(); i++)
      result[i] = i;
    
    return result;
  }
}