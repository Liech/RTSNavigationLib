#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace RTSPathingLib {
  class svg {
  public:
    void write(const std::string& filename, const glm::dvec2& startRegion = glm::dvec2(0, 0), const glm::dvec2& size = glm::dvec2(5, 5)) const;
    static void write(const std::string& filename, const std::vector<svg>& streaks, const glm::dvec2& startRegion = glm::dvec2(0, 0), const glm::dvec2& size = glm::dvec2(5, 5));
    std::string getXML(const glm::dvec2& startRegion, const glm::dvec2& size) const;

    std::vector<glm::dvec2> streak;
    std::string            color = "black";
    double                  thickness = 0.01;
    bool                   filled = false;
    bool                   wrapAround = false;
    std::string            text = "";
  };
}