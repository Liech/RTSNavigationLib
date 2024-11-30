#include "AssignmentProblemDualKDTree.h"

#include <algorithm>


namespace RTSNavigationLib
{
  void AssignmentProblemDualKDTree::recurse(std::vector<size_t>& result, std::vector<size_t>& workerI, std::vector<size_t>& placesI, const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& places, bool yaxis)
  {
    assert(placesI.size() == workerI.size());
    if (workerI.size() == 1)
    {
      result[workerI[0]] = placesI[0];
    }
    else if (workerI.size() > 1) {
      if (yaxis) {
        std::ranges::sort(workerI, [&workers](const size_t& a, const size_t& b)->bool {return workers.at(a).y < workers.at(b).y; });
        std::ranges::sort(placesI, [&places](const size_t& a, const size_t& b)->bool {return places.at(a).y < places.at(b).y; });
      }
      else {
        std::ranges::sort(workerI, [&workers](const size_t& a, const size_t& b)->bool {return workers.at(a).x < workers.at(b).x; });
        std::ranges::sort(placesI, [&places](const size_t& a, const size_t& b)->bool {return places.at(a).x < places.at(b).x; });
      }
      size_t leftAmount = workerI.size() / 2;
      auto workerL = std::vector<size_t>(workerI.begin(), workerI.begin() + leftAmount);
      auto placesL = std::vector<size_t>(placesI.begin(), placesI.begin() + leftAmount);
      auto workerR = std::vector<size_t>(workerI.begin() + leftAmount, workerI.end());
      auto placesR = std::vector<size_t>(workerI.begin() + leftAmount, workerI.end());

      recurse(result, workerL, placesL, workers, places, !yaxis);
      recurse(result, workerR, placesR, workers, places, !yaxis);
    }
  }

  std::vector<size_t> AssignmentProblemDualKDTree::getTickets(const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& assignments)
  {
    assert(workers.size() == places.size());

    std::vector<size_t> workerI;
    std::vector<size_t> placesI;
    for (size_t i = 0; i < workers.size(); i++)
      workerI.push_back(i);
    for (size_t i = 0; i < workers.size(); i++)
      placesI.push_back(i);

    std::vector<size_t> result;
    result.resize(workers.size());

    recurse(result, workerI, placesI, workers, assignments, false);

    return result;
  }
}