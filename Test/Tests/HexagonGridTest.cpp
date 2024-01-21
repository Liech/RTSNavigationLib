#include <catch2/catch_test_macros.hpp>

#include <RTSNavigationLib/Util/HexagonGrid/TopFlatHexGrid.h>
#include <RTSNavigationLib/Util/HexagonGrid/HexGridSvg.h>
#include <RTSNavigationLib/Util/HexagonGrid/Hex2DVoxelizer.h>
#include <RTSNavigationLib/Util/svg.h>

namespace HexagonGridTests {
  TEST_CASE("HexagonGrid/voxelizer", "[HexagonVoxelizer]") {
    glm::ivec2 dimension = glm::ivec2(6, 6);

    std::vector<glm::dvec2> polygon;
    glm::dvec2 offset = glm::dvec2(1, 1);
    double scale = 0.6;
    polygon.push_back(offset + glm::dvec2(1, 0) * scale);
    polygon.push_back(offset + glm::dvec2(3, 0) * scale);
    polygon.push_back(offset + glm::dvec2(4.5, 6) * scale);
    polygon.push_back(offset + glm::dvec2(0, 4) * scale);
    polygon.push_back(offset + glm::dvec2(1, 0) * scale);

    auto t = RTSNavigationLib::Hex2DVoxelizer::voxelize(polygon, dimension, glm::dvec2(0, 0), 1);
    if (false) {
      RTSNavigationLib::svg v;
      v.streak = polygon;
      v.color = "blue";
      std::vector<RTSNavigationLib::svg> x = RTSNavigationLib::HexGridSvg::write(t, 1);
      x.push_back(v);
      RTSNavigationLib::svg::write("VoxelizerTest.svg", x, glm::dvec2(-5, -5), glm::dvec2(30, 30));
    }

    std::vector<bool> r = {
      false,false,false,false,false,false,
      false,false,false,true ,false,false,
      false,false,true ,true ,true ,false,
      false,false,true ,true ,true ,false,
      false,false,false,true ,true ,false,
      false,false,false,false,false,false
    };

    REQUIRE(t.data.size() == r.size());
    REQUIRE(t.data == r);
  }
}