#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>

namespace RTSNavigationLib {
  class AssignmentProblemDualKDTree
  {
  public:
    static std::vector<size_t> getTickets(const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& assignments);
  private:
    static void recurse(std::vector<size_t>& result, std::vector<size_t>& workerI, std::vector<size_t>& placesI, const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& places, bool yaxis);
  };
}