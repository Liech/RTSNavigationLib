#include "svg.h"

#include "String2File.h"

namespace RTSPathingLib {
  void svg::write(const std::string& filename, const glm::dvec2& startRegion, const glm::dvec2& size) const {
    write(filename, { *this }, startRegion,size);
  }

  void svg::write(const std::string& filename, const std::vector<svg>& streaks, const glm::dvec2& startRegion, const glm::dvec2& size) {
    std::string data = "<svg viewBox=\"" + std::to_string(startRegion.x) + " " + std::to_string(startRegion.y) + " " + std::to_string(size.x) + " " + std::to_string(size.x) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for (const auto& x : streaks)
      data += x.getXML(startRegion,size);

    auto line = [&data, startRegion,size](glm::dvec2 start, glm::dvec2 end) {
      start.y = startRegion.y + size.y - (start.y-startRegion.y);
      end  .y = startRegion.y + size.y - (end  .y-startRegion.y);
      data += "  <line x1=\"" + std::to_string(start.x) + "\" y1=\"" + std::to_string(start.y) + "\" x2=\"" + std::to_string(end.x) + "\" y2=\"" + std::to_string(end.y) + "\" stroke=\"black\"   stroke-width=\"0.1\"/>";
      };

    glm::dvec2 arrowFoot  = startRegion + glm::dvec2(3,3+0);
    glm::dvec2 arrowTip   = startRegion + glm::dvec2(3,3+2);
    glm::dvec2 arrowLeft  = startRegion + glm::dvec2(2,4);
    glm::dvec2 arrowRight = startRegion + glm::dvec2(4,4);
    line(arrowFoot, arrowTip  );
    line(arrowTip , arrowLeft );
    line(arrowTip , arrowRight);


    data += "\n</svg>";
    RTSPathingLib::String2File(filename, data);
  }

  std::string svg::getXML(const glm::dvec2& startRegion, const glm::dvec2& size) const {
    std::string result = "";

    auto line = [&result, startRegion,size](glm::dvec2 start, glm::dvec2 end, std::string color, double thickness) {
      start.y = startRegion.y + size.y - (start.y - startRegion.y);
      end.y   = startRegion.y + size.y - (end.y   - startRegion.y);
      result += "  <line x1=\"" + std::to_string(start.x) + "\" y1=\"" + std::to_string(start.y) + "\" x2=\"" + std::to_string(end.x) + "\" y2=\"" + std::to_string(end.y) + "\" stroke=\"" + color + "\" stroke-width=\"" + std::to_string(thickness) + "\"/>";
      };

    if (!filled) {
      for (size_t i = 1; i < streak.size(); i++) {
        glm::dvec2 start = streak[i];
        glm::dvec2 end = streak[i - 1];
        line(start, end, color, thickness);
      }
      if (wrapAround)
        line(streak[streak.size() - 1], streak[0], color, thickness);
    }
    else {
      result += "<polygon points=\"";
      for (size_t i = 0; i < streak.size(); i++) {
        glm::dvec2 point = streak[i];
        point.y = startRegion.y + size.y - (point.y - startRegion.y);
        result += std::to_string(point.x) + "," + std::to_string(point.y) + " ";
      }
      result += "\" fill=\"" + color + "\" />\n";
    }

    return result;
  }
}