#include "Usher.h"


#include "Body.h"
#include "BodyUtil.h"
#include "Util/svg.h"
#include "Util/AssignmentProblemSolver.h"


namespace RTSPathingLib {
  Usher::Usher() {

  }

  std::vector<size_t> Usher::assignPlaces(const std::vector<Body>& units, const std::vector<Body>& places) {
    auto costFunction = [](const glm::dvec2& a, const glm::dvec2& b) { 
      return std::pow(glm::distance(a, b)+1.0,4); // higher emphasis on distance reducing by exponentialize the impact
      //return glm::distance(a, b);
      };

    struct entry {
      std::vector<glm::dvec2> problemInput;
      std::vector<size_t>     indices;
    };
    std::map<std::pair<size_t, size_t>, entry> AllWorker;
    std::map<std::pair<size_t, size_t>, entry> AllTasks;
    std::vector<std::pair<size_t, size_t>> keys;

    for (size_t i = 0; i < units.size(); i++) {
      auto& unit = units[i];
      auto key = std::make_pair(unit.category, unit.size);
      if (AllWorker.count(key) == 0) {
        AllWorker[key] = entry();
        keys.push_back(key);
      }
      auto& worker = AllWorker[key];
      worker.indices.push_back(i);
      worker.problemInput.push_back(unit.position);
    }
    for (size_t i = 0; i < places.size(); i++) {
      auto& place = places[i];
      auto key = std::make_pair(place.category, place.size);
      if (AllTasks.count(key) == 0)
        AllTasks[key] = {};
      auto& tasks = AllTasks[key];
      tasks.indices.push_back(i);
      tasks.problemInput.push_back(place.position);
    }

    std::vector<size_t> result;
    result.resize(units.size());
    for (auto& key : keys) {
      auto& worker = AllWorker[key];
      auto& tasks  = AllTasks[key];
      AssignmentProblemSolver<glm::dvec2, glm::dvec2> solver(worker.problemInput,tasks.problemInput, costFunction);
      std::vector<size_t> subSolution = solver.getTickets();
      for (size_t i = 0; i < subSolution.size(); i++) {
        size_t ticket = subSolution[i];
        result[worker.indices[i]] = tasks.indices[ticket];
      }
    }
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
    svg::write("Usher.svg", svgDebug, glm::dvec2(-10, -10), glm::dvec2(20, 20));
  }
}