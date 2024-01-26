#pragma once

#include <glm/glm.hpp>
#include <vector>

//https://www.numerical-tours.com/matlab/fastmarching_0_implementing/
//https://github.com/bergolho/EikonalEquation/tree/master
//https://gamedev.stackexchange.com/questions/387/how-does-flow-field-pathfinding-work
//https://math.berkeley.edu/~sethian/2006/Explanations/fast_marching_explain.html

namespace RTSNavigationLib {
  class EikonalGrid { //Fast Marching Method
  public:
    EikonalGrid(const std::vector<float>& obstacles, const glm::ivec2& resolution, const glm::ivec2& target);

    glm::ivec2 getResolution() const;
    glm::ivec2 getTarget()     const;
    float getDistance(const glm::ivec2& position) const;
    float getDistance(const size_t& position) const;
  private:
    void  initGrid(const std::vector<float>& obstacles);
    float getWeight(const glm::ivec2& pos, const std::vector<float>& obstacles) const;

    glm::ivec2 target;
    glm::ivec2 resolution;
    std::vector<float> grid;
  };
}