#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>

namespace RTSNavigationLib {
  //splits recursivly the positions similar to a kd tree with alternating sort axis
  //but the alternating axis proved less effective than measuring the main axis of the positions for splitting
  //
  //Results in not 100% correct, but O(n*log(n)) fast results (compared to mcf with O(n^3))
  //similar implementation to the DistributeUniform.h problem

  class AssignmentProblemDualKDTree
  {
  public:
    static std::vector<size_t> getTickets(const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& assignments);
  private:
    static void recurse(std::vector<size_t>& result, std::vector<size_t>& workerI, std::vector<size_t>& placesI, const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& places, bool yaxis);
    static bool findMainAxis(const std::vector<size_t>& workerI, const std::vector<size_t>& placesI, const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& places);
  };
}