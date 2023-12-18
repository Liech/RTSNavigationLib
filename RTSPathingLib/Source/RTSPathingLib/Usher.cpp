#include "Usher.h"


#include "Body.h"
#include "BodyUtil.h"
#include "Util/RTree2D.h"

//https://stackoverflow.com/questions/35746487/min-cost-max-flow-with-boostsuccessive-shortest-path-nonnegative-weights
//https://www.boost.org/doc/libs/1_83_0/libs/graph/doc/successive_shortest_path_nonnegative_weights.html

namespace RTSPathingLib {
  Usher::Usher() {

  }

  std::vector<size_t> Usher::assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places) {
    std::vector<size_t> result;
    result.resize(units.size());

    std::vector<std::pair<glm::vec2, size_t>> placesTreeInput;
    placesTreeInput.reserve(places.size());
    size_t placeCounter = 0;
    for (auto& x : places) {
      placesTreeInput.push_back(std::make_pair(x.position, placeCounter));
      placeCounter++;
    }
    RTree2D placesTree(placesTreeInput);

    struct walk {
      size_t place;
      size_t unit;
      float distance;
    };
    std::vector<walk> distances;
    size_t unitCounter = 0;
    //flawed: instead search iterativly for the greatest distance
    
    for (const auto& x : units) {
      walk sub;
      sub.unit = unitCounter;
      size_t neighbor = placesTree.nearestNeighbour(x.position)[0];
      placesTree.remove(neighbor);
      sub.place = neighbor;
      sub.distance = glm::distance(units[sub.unit].position, places[sub.place].position);
      distances.push_back(sub);
      unitCounter++;
    }


    glm::vec2 PlaceCenter = BodyUtil::getCenter(places);
    glm::vec2 mainDirection = glm::vec2(1, 0);
    glm::vec2 sideDirection = glm::vec2(0, 1);

    //just assign naive as ordered
    for (size_t i = 0; i < units.size(); i++)
      result[i] = i;
    
    return result;
  }

  
}