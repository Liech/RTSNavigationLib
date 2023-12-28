#include "Usher.h"


#include "Body.h"
#include "BodyUtil.h"
#include "Util/RTree2D.h"
#include "Util/svg.h"

//https://stackoverflow.com/questions/35746487/min-cost-max-flow-with-boostsuccessive-shortest-path-nonnegative-weights
//https://www.boost.org/doc/libs/1_83_0/libs/graph/doc/successive_shortest_path_nonnegative_weights.html

namespace RTSPathingLib {
  Usher::Usher() {

  }

  std::vector<size_t> Usher::assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places) {
    std::vector<size_t> result;
    result.resize(units.size());

    std::unique_ptr<RTree2D>   placesTree = buildTree(places);
    std::vector<Usher::ticket> ranking    = firstEstimate(units, places, *placesTree);

    while (ranking.size() > 1) {
      std::sort(ranking.begin(), ranking.end(), [](const Usher::ticket& a, const Usher::ticket& b) {
        return a.distance > b.distance;
        });
      Usher::ticket worst = ranking[0];
      ranking.erase(ranking.begin() + 0);
      placesTree->remove(worst.place);
      result[worst.unit] = worst.place;

      //repair ranking
      for (auto& x : ranking) {
        if (x.place == worst.place) {
          x.place = placesTree->nearestNeighbour(units[x.unit].position)[0];
          x.distance = glm::distance(units[x.unit].position, places[x.place].position);
        }
      }
    }
    if (ranking.size() == 1)
      result[ranking[0].unit] = ranking[0].place;

    return result;
  }

  std::vector<Usher::ticket> Usher::firstEstimate(const std::vector<Body>& units, const std::vector<Body>& places, RTree2D& placesTree) {
    std::vector<ticket> result;
    size_t unitCounter = 0;

    for (const auto& x : units) {
      ticket sub;
      sub.unit = unitCounter;
      size_t neighbor = placesTree.nearestNeighbour(x.position)[0];
      sub.place = neighbor;
      sub.distance = glm::distance(units[sub.unit].position, places[sub.place].position);
      result.push_back(sub);
      unitCounter++;
    }
    return result;
  }

  std::unique_ptr<RTree2D> Usher::buildTree(const std::vector<Body>& places) {
    std::vector<std::pair<glm::dvec2, size_t>> placesTreeInput;
    placesTreeInput.reserve(places.size());
    size_t placeCounter = 0;
    for (auto& x : places) {
      placesTreeInput.push_back(std::make_pair(x.position, placeCounter));
      placeCounter++;
    }
    return std::make_unique<RTree2D>(placesTreeInput);
  }

  void Usher::visualize(const std::vector<size_t>& usherResult, const std::vector<Body>& units, const std::vector<Body>& places) {
    std::vector<svg> svgDebug = {};


    size_t counter = 0;
    for (auto& body : places) {
      svg debug;
      debug.streak = {
            body.position + glm::dvec2(-0.5 ,-0.5) * (double)body.size * 0.5,
            body.position + glm::dvec2( 0.5 ,-0.5) * (double)body.size * 0.5,
            body.position + glm::dvec2( 0.5 , 0.5) * (double)body.size * 0.5,
            body.position + glm::dvec2(-0.5 , 0.5) * (double)body.size * 0.5,
      };
      debug.filled = true;
      debug.color = "gray";
      debug.thickness = 0.1;
      debug.text = std::to_string(counter);
      svgDebug.push_back(debug);
      counter++;
    }
    counter = 0;
    for (auto& body : units) {
      svg debug;
      debug.streak = {
            body.position + glm::dvec2(-0.5 ,-0.5) * (double)body.size * 0.1,
            body.position + glm::dvec2(0.5 ,-0.5) * (double)body.size * 0.1,
            body.position + glm::dvec2(0.5 , 0.5) * (double)body.size * 0.1,
            body.position + glm::dvec2(-0.5 , 0.5) * (double)body.size * 0.1,
      };
      debug.filled = true;
      debug.color = "green";
      debug.thickness = 0.1;
      debug.text = std::to_string(counter);
      svgDebug.push_back(debug);
      counter++;
    }
    for (size_t i = 0; i < usherResult.size();i++) {
      svg debug;
      size_t ticket = usherResult[i];
      debug.streak = {
            units[i].position, 
            places[ticket].position
      };
      debug.color = "yellow";
      debug.thickness = 0.1;
      svgDebug.push_back(debug);
    }
    svg::write("Usher.svg", svgDebug, glm::dvec2(-10, -10), glm::dvec2(20, 20));
  }

  void Usher::assignPlaces2() {

  }
}