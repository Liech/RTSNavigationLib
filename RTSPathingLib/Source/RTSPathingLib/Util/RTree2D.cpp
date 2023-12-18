#include "RTree2D.h"

#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "glmBoostGeometry.h"
BOOST_GEOMETRY_REGISTER_POINT_2D(glm::vec2, float, cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_BOX(glm2dBox, glm::vec2, lowLeft, upRight)

class RTree2D::RTreeImpl {
public:
  std::unique_ptr<boost::geometry::index::rtree<std::pair<glm::vec2, size_t>, boost::geometry::index::dynamic_rstar>> tree = nullptr;
  std::map<size_t,std::pair<glm::vec2, size_t>> data;
};

RTree2D::RTree2D(const std::vector<std::pair<glm::vec2, size_t>>& bulkInput) {
  p = std::make_unique<RTree2D::RTreeImpl>();
  p->tree = std::make_unique<boost::geometry::index::rtree<std::pair<glm::vec2, size_t>, boost::geometry::index::dynamic_rstar>>(bulkInput, boost::geometry::index::dynamic_rstar(bulkInput.size()));
  
  for (const auto& x : bulkInput)
    p->data[x.second] = x;
}

RTree2D::~RTree2D() {

}

std::vector<size_t> RTree2D::boxQuery(const glm::vec2& lowLeftBox, const glm::vec2& upRightBox) {
  std::vector<std::pair<glm::vec2, size_t>> preResult;
  glm2dBox box1(lowLeftBox,upRightBox);
  p->tree->query(boost::geometry::index::covered_by(box1), std::back_inserter(preResult));

  std::vector<size_t> result;
  result.reserve(preResult.size());
  for (auto& x : preResult)
    result.push_back(x.second);
  return result;
}

std::vector<size_t> RTree2D::nearestNeighbour(const glm::vec2 position, size_t amount) {
  //https://gist.github.com/warrenrentlytics/c9a1836a40d4fcbba28a7e29357dad7d
  std::vector<std::pair<glm::vec2, size_t>> preResult;
  p->tree->query(boost::geometry::index::nearest(position, amount), std::back_inserter(preResult));

  std::vector<size_t> result;
  result.reserve(preResult.size());
  for (auto& x : preResult)
    result.push_back(x.second);
  return result;
}

void RTree2D::remove(size_t index) {
  p->tree->remove(p->data[index]);
  p->data.erase(index);
}