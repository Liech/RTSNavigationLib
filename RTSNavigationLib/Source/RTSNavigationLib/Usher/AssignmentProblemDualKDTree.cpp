#include "AssignmentProblemDualKDTree.h"

#include <algorithm>
#include <iostream>


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
        std::ranges::sort(workerI, [&workers](const size_t& a, const size_t& b)->bool {
          if (workers.at(a).y == workers.at(b).y) 
            return workers.at(a).x < workers.at(b).x;
          return workers.at(a).y < workers.at(b).y; 
          });
        std::ranges::sort(placesI, [&places](const size_t& a, const size_t& b)->bool {
          if (places.at(a).y == places.at(b).y) 
            return places.at(a).x < places.at(b).x;
          return places.at(a).y < places.at(b).y; });
      }
      else {
        std::ranges::sort(workerI, [&workers](const size_t& a, const size_t& b)->bool {
          if (workers.at(a).x == workers.at(b).x) 
            return workers.at(a).y < workers.at(b).y;
          return workers.at(a).x < workers.at(b).x; });
        std::ranges::sort(placesI, [&places](const size_t& a, const size_t& b)->bool {
          if (places.at(a).x == places.at(b).x) 
            return places.at(a).y < places.at(b).y;
          return places.at(a).x < places.at(b).x; });
      }
      size_t leftAmount = workerI.size() / 2;
      auto workerL = std::vector<size_t>(workerI.begin(), workerI.begin() + leftAmount);
      auto placesL = std::vector<size_t>(placesI.begin(), placesI.begin() + leftAmount);
      auto workerR = std::vector<size_t>(workerI.begin() + leftAmount, workerI.end());
      auto placesR = std::vector<size_t>(placesI.begin() + leftAmount, placesI.end());

      bool mainAxisL = findMainAxis(workerL, placesL, workers, places);
      bool mainAxisR = findMainAxis(workerR, placesR, workers, places);
      //std::cout << workerL.size() <<"/" <<workerR.size() << "  " << placesL.size() <<"/" <<placesR.size()<< " --- " << mainAxisL << "/" << mainAxisR << " ("<< yaxis<<")"<< std::endl;
      
      //if (yaxis) std::cout << "y: "; else std::cout << "x: ";
      //std::cout << "( ";
      //if (mainAxisL) std::cout << "yW: "; else std::cout << "xW: ";
      //for (auto& x : workerL) std::cout << "|" << x;
      //std::cout << ")";
      //std::cout << " ( ";
      //if (mainAxisR) std::cout << "yW: "; else std::cout << "xW: ";
      //for (auto& x : workerR) std::cout << "|" << x;
      //std::cout << ")  ----- ";
      //
      //std::cout << "( ";
      //if (mainAxisL) std::cout << "yP: "; else std::cout << "xP: ";
      //for (auto& x : placesL) std::cout << "|" << x;
      //std::cout << ")";
      //std::cout << " ( ";
      //if (mainAxisR) std::cout << "yP: "; else std::cout << "xP: ";
      //for (auto& x : placesR) std::cout << "|" << x;
      //std::cout << ")";


      //std::cout<<std::endl;

      recurse(result, workerL, placesL, workers, places, mainAxisL);
      recurse(result, workerR, placesR, workers, places, mainAxisR);
    }
  }

  bool AssignmentProblemDualKDTree::findMainAxis(const std::vector<size_t>& workerI, const std::vector<size_t>& placesI, const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& places)
  {
    glm::dvec2 center = glm::dvec2(0, 0);
    for (const auto& x : placesI)
      center += places[x];
    center /= placesI.size();

    glm::dvec2 cumVec = glm::dvec2(0, 0);
    for (const auto& X : placesI) {
      const auto& x = places[X];
      auto dir = x - center;
      cumVec += glm::dvec2(std::abs(dir.x), std::abs(dir.y));
    }
    cumVec = glm::normalize(cumVec);
    return std::abs(cumVec.y) > std::abs(cumVec.x);
  }

  std::vector<size_t> AssignmentProblemDualKDTree::getTickets(const std::vector<glm::dvec2>& workers, const std::vector<glm::dvec2>& places)
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

    bool startAxis = findMainAxis(workerI, placesI, workers, places);
    recurse(result, workerI, placesI, workers, places, startAxis);

    return result;
  }
}