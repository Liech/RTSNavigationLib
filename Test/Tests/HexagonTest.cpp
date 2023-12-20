#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/Util/HexagonGrid/TopFlatHexGrid.h>
#include <RTSPathingLib/Util/HexagonGrid/HexGridSvg.h>
#include <RTSPathingLib/Util/HexagonGrid/Hex2DVoxelizer.h>
#include <RTSPathingLib/Util/svg.h>

TEST_CASE("Hexagon/voxelizer", "[HexagonVoxelizer]") {
  glm::ivec2 dimension = glm::ivec2(6, 6);

  std::vector<glm::vec2> polygon;
  glm::vec2 offset = glm::vec2(1, 1);
  float scale = 0.6;
  polygon.push_back(offset + glm::vec2(1, 0) * scale);
  polygon.push_back(offset + glm::vec2(3, 0) * scale);
  polygon.push_back(offset + glm::vec2(4.5, 6) * scale);
  polygon.push_back(offset + glm::vec2(0, 4) * scale);  
  polygon.push_back(offset + glm::vec2(1, 0) * scale);

  auto t = RTSPathingLib::Hex2DVoxelizer::voxelize(polygon, dimension, glm::vec2(0,0),1);
  if (false) {
    RTSPathingLib::svg v;
    v.streak = polygon;
    v.color = "blue";
    std::vector<RTSPathingLib::svg> x = RTSPathingLib::HexGridSvg::write(t, 1);
    x.push_back(v);
    RTSPathingLib::svg::write("VoxelizerTest.svg", x, glm::vec2(-5, -5), glm::vec2(30, 30));
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