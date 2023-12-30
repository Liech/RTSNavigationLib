#include "RTree2D.h"

#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "glmBoostGeometry.h"
BOOST_GEOMETRY_REGISTER_POINT_2D(glm::dvec2, double, cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_BOX(RTSPathingLib::glm2dBox, glm::dvec2, lowLeft, upRight)

namespace RTSPathingLib {
  //https://stackoverflow.com/questions/34951426/cannot-remove-element-from-boostgeometryindexrtree-by-its-index
  template <typename Rtree, typename Id>
  size_t remove_ids_bulk(Rtree& rtree, Id const& id) {
    using V = typename Rtree::value_type;
    std::vector<V> v;
    std::copy_if(rtree.begin(), rtree.end(), back_inserter(v), [id](V const& v) { return v.second == id; });

    return rtree.remove(v.begin(), v.end());
  }

  class RTree2D::RTreeImpl {
  public:
    std::unique_ptr<boost::geometry::index::rtree<std::pair<glm::dvec2, size_t>, boost::geometry::index::dynamic_rstar>> tree = nullptr;
    std::map<size_t, std::pair<glm::dvec2, size_t>> data;
  };

  RTree2D::RTree2D(const std::vector<std::pair<glm::dvec2, size_t>>& bulkInput) {
    p = std::make_unique<RTree2D::RTreeImpl>();
    p->tree = std::make_unique<boost::geometry::index::rtree<std::pair<glm::dvec2, size_t>, boost::geometry::index::dynamic_rstar>>(bulkInput, boost::geometry::index::dynamic_rstar(bulkInput.size()));

    for (const auto& x : bulkInput)
      p->data[x.second] = x;
  }

  RTree2D::~RTree2D() {

  }

  std::vector<size_t> RTree2D::boxQuery(const glm::dvec2& lowLeftBox, const glm::dvec2& upRightBox) {
    std::vector<std::pair<glm::dvec2, size_t>> preResult;
    glm2dBox box1(lowLeftBox, upRightBox);
    p->tree->query(boost::geometry::index::covered_by(box1), std::back_inserter(preResult));

    std::vector<size_t> result;
    result.reserve(preResult.size());
    for (auto& x : preResult)
      result.push_back(x.second);
    return result;
  }

  std::vector<size_t> RTree2D::nearestNeighbour(const glm::dvec2 position, size_t amount) {
    //https://gist.github.com/warrenrentlytics/c9a1836a40d4fcbba28a7e29357dad7d
    std::vector<std::pair<glm::dvec2, size_t>> preResult;
    p->tree->query(boost::geometry::index::nearest(position, amount), std::back_inserter(preResult));

    std::vector<size_t> result;
    result.reserve(preResult.size());
    for (auto& x : preResult)
      result.push_back(x.second);
    return result;
  }

  void RTree2D::remove(size_t index) {
    remove_ids_bulk(*p->tree, index);
    p->data.erase(index);
  }
}