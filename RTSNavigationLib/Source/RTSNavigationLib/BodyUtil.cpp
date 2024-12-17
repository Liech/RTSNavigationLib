#include "BodyUtil.h"

#include "WorldBody.h"

namespace RTSNavigationLib
{

    WorldBody BodyUtil::transform(const WorldBody& b, const glm::dmat4& transformation)
    {
        WorldBody result = b;
        result.position  = transformation * glm::vec4(b.position, 0, 1);
        return result;
    }

    std::vector<WorldBody> BodyUtil::transform(const std::vector<WorldBody>& b, const glm::dmat4& transformation)
    {
        std::vector<WorldBody> result;
        result.resize(b.size());

        for (size_t i = 0; i < b.size(); i++)
        {
            result[i]          = b[i];
            result[i].position = transformation * glm::vec4(b[i].position, 0, 1);
        }

        return result;
    }

    glm::dvec2 BodyUtil::getCenter(const std::vector<WorldBody>& b)
    {
        glm::dvec2 result = glm::dvec2(0, 0);
        for (const auto& x : b)
        {
            result += x.position;
        }
        result = glm::dvec2(result[0] / b.size(), result[1] / b.size());
        return result;
    }
}