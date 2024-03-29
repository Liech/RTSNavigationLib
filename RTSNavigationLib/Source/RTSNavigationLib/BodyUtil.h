#pragma

#include <vector>
#include <glm/glm.hpp>

namespace RTSNavigationLib {
  struct Body;

  class BodyUtil {
  public:
    static Body              transform  (const Body& b, const glm::dmat4& transformation);
    static std::vector<Body> transform  (const std::vector<Body>& b, const glm::dmat4& transformation);
    static glm::dvec2         getCenter  (const std::vector<Body>& b);
  };
}