#pragma

#include <vector>
#include <glm/glm.hpp>

namespace RTSPathingLib {
  class Body;

  class BodyUtil {
  public:
    static Body              transform(const Body& b, const glm::mat4& transformation);
    static std::vector<Body> transform(const std::vector<Body>& b, const glm::mat4& transformation);
  };
}