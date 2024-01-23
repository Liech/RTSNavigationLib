//#include "FlowField.h"
//
//#include "DijkstraGrid.h"
//
//namespace RTSNavigationLib {
//  FlowField::FlowField(const std::vector<float>& obstacles, const glm::ivec2& resolution_, const glm::ivec2& target_) {
//    resolution = resolution_;
//    target     = target_;
//
//    initField(obstacles);
//  }
//
//  glm::dvec2 FlowField::getDirection(const glm::ivec2& location) const {
//    size_t address = location.x + location.y * resolution.x;
//    return field[address];
//  }
//
//  void FlowField::initField(const std::vector<float>& obstacles) {
//    field.resize(resolution.x * resolution.y, glm::vec2(0, 0));
//    DijkstraGrid dijkstra(obstacles, resolution, target);
//    
//    size_t size = resolution.x * resolution.y;
//#pragma omp parallel for
//    for (long long address = 0; address < size; address++) {
//      glm::ivec2 pos = glm::ivec2(address % resolution.x, address / resolution.x);
//      glm::ivec2 best = glm::ivec2(0, 0);
//      for(int x = -1;x < 2;x++)
//        for (int y = -1; y < 2; y++) {
//          if (x == 0 && y == 0)
//            continue;
//
//        }
//    }
//
//  }
//}