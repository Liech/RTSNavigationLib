#pragma once

#include <vector>
#include <glm/glm.hpp>

//https://howtorts.github.io/2014/01/04/basic-flow-fields.html
//https://www.jdxdev.com/blog/2020/05/03/flowfields/
//https://www.gameaipro.com/GameAIPro/GameAIPro_Chapter23_Crowd_Pathfinding_and_Steering_Using_Flow_Field_Tiles.pdf
//https://www.sanctuaryshatteredsun.com/post/pathfinding-1
//https://howtorts.github.io/
//https://howtorts.github.io/2014/01/05/flow-field-improvements.html
//https://github.com/bjkarasek/flowfield-unity  //Eikonal 

namespace RTSNavigationLib {
  class DijkstraGrid;
  class EikonalGrid;

  class FlowField {
  public:
    FlowField(const DijkstraGrid& grid);
    FlowField(const EikonalGrid&  grid);

    glm::ivec2 getResolution() const;
    std::vector<glm::ivec2> getTargets()     const;
    glm::dvec2 getDirection(const glm::ivec2& location) const;
  private:

    void initField(const DijkstraGrid& grid);
    void initField(const EikonalGrid& grid);

    static constexpr glm::dvec2 lookup(unsigned char);

    glm::ivec2                    resolution;
    std::vector<glm::ivec2>       targets;

    //lookuptable id for vector. basicly a unit vector of 360/255°
    std::vector<unsigned char>    field;
  };
}