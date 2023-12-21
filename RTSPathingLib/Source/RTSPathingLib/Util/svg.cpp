#include "svg.h"

#include "String2File.h"

namespace RTSPathingLib {
  void svg::write(const std::string& filename, const glm::vec2& startRegion, const glm::vec2& size) const {
    write(filename, { *this }, startRegion,size);
  }

  void svg::write(const std::string& filename, const std::vector<svg>& streaks, const glm::vec2& startRegion, const glm::vec2& size) {
    std::string data = "<svg viewBox=\"" + std::to_string(startRegion.x) + " " + std::to_string(startRegion.y) + " " + std::to_string(size.x) + " " + std::to_string(size.x) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for (const auto& x : streaks)
      data += x.getXML();

    data += "\n</svg>";
    RTSPathingLib::String2File(filename, data);
  }

  std::string svg::getXML() const {
    std::string result = "";

    if (!filled) {
      for (size_t i = 1; i < streak.size(); i++) {
        glm::dvec2 start = streak[i];
        glm::dvec2 end = streak[i - 1];
        result += "<line x1 = \"" + std::to_string(start.x) + "\" y1 = \"" + std::to_string(start.y) + "\" x2 = \"" + std::to_string(end.x) + "\" y2 = \"" + std::to_string(end.y) + "\" stroke = \"" + color + "\" stroke-width=\"" + std::to_string(thickness) + "\"  />\n";
      }
      if (wrapAround)
        result += "<line x1 = \"" + std::to_string(streak[streak.size()-1].x) + "\" y1 = \"" + std::to_string(streak[streak.size()-1].y) + "\" x2 = \"" + std::to_string(streak[0].x) + "\" y2 = \"" + std::to_string(streak[0].y) + "\" stroke = \"" + color + "\" stroke-width=\"" + std::to_string(thickness) + "\"  />\n";
    }
    else {
      result += "<polygon points=\"";
      for (size_t i = 0; i < streak.size(); i++) {
        result += std::to_string(streak[i].x) + "," + std::to_string(streak[i].y) + " ";
      }
      result += "\" fill=\"" + color + "\" />\n";
    }
    return result;
  }
}