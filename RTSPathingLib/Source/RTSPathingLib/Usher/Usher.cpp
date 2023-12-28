#include "Usher.h"


#include "Body.h"
#include "BodyUtil.h"
#include "Util/svg.h"
#include "Util/AssignmentProblemSolver.h"


namespace RTSPathingLib {
  Usher::Usher() {

  }

  std::vector<size_t> Usher::assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places) {
    auto costFunction = [](const glm::dvec2& a, const glm::dvec2& b) { return glm::distance(a, b); };

    std::vector<glm::dvec2> worker;
    worker.reserve(units.size());
    for (auto& unit : units)
      worker.push_back(unit.position);

    std::vector<glm::dvec2> tasks;
    tasks.reserve(places.size());
    for (auto& place : places)
      tasks.push_back(place.position);

    AssignmentProblemSolver<glm::dvec2, glm::dvec2> solver(worker, tasks,costFunction);

    auto result = solver.getTickets();
    return result;
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
}