#pragma

#include <glm/glm.hpp>
#include <vector>

namespace RTSNavigationLib
{
    struct WorldBody;

    class BodyUtil
    {
      public:
        static WorldBody              transform(const WorldBody& b, const glm::dmat4& transformation);
        static std::vector<WorldBody> transform(const std::vector<WorldBody>& b, const glm::dmat4& transformation);
        static glm::dvec2             getCenter(const std::vector<WorldBody>& b);
    };
}