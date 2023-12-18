#include "Usher.h"


#include "Body.h"
#include "BodyUtil.h"


//https://stackoverflow.com/questions/35746487/min-cost-max-flow-with-boostsuccessive-shortest-path-nonnegative-weights
//https://www.boost.org/doc/libs/1_83_0/libs/graph/doc/successive_shortest_path_nonnegative_weights.html

namespace RTSPathingLib {
  Usher::Usher() {

  }

  std::vector<size_t> Usher::assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places) {
    std::vector<size_t> result;
    result.resize(units.size());

    glm::vec2 PlaceCenter = BodyUtil::getCenter(places);
    glm::vec2 mainDirection = glm::vec2(1, 0);
    glm::vec2 sideDirection = glm::vec2(0, 1);

    //just assign naive as ordered
    for (size_t i = 0; i < units.size(); i++)
      result[i] = i;
    
    return result;
  }

  
}