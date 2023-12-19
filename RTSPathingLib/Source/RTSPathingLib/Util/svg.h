#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

class svg {
public:
  void write(const std::string& filename) const;
  static void write(const std::string& filename, const std::vector<svg>& streaks, const glm::vec2& startRegion = glm::vec2(0, 0), const glm::vec2& endRegion = glm::vec2(5, 5));
  std::string getXML() const;

  std::vector<glm::vec2> streak;
  std::string            color       = "black";
  float                  thickness   = 0.01f;
  bool                   filled      = false;
};