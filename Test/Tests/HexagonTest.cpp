#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/Hexagon/TopFlatHexGrid.h>
#include <RTSPathingLib/Hexagon/HexGridSvg.h>
#include <RTSPathingLib/Util/svg.h>
#include <RTSPathingLib/Hexagon/Hex2DVoxelizer.h>

TEST_CASE("Hexagon/wub", "[Hexagon]") {
  glm::ivec2 dimension = glm::ivec2(20, 20);

  std::vector<glm::vec2> polygon;
  glm::vec2 offset = glm::vec2(4, 4);
  float scale = 5;
  polygon.push_back(offset + glm::vec2(0, 0) * scale);
  polygon.push_back(offset + glm::vec2(1, 0) * scale);
  polygon.push_back(offset + glm::vec2(1, 1) * scale);
  polygon.push_back(offset + glm::vec2(0, 1) * scale);  
  polygon.push_back(offset + glm::vec2(0, 0) * scale);
  svg v;
  v.streak = polygon;
  v.color = "blue";

  auto t = Hex2DVoxelizer::voxelize(polygon, dimension, glm::vec2(0,0),1);
  std::vector<svg> x = HexGridSvg::write(t, 1);

  x.push_back(v);
  svg::write("Hello.svg", x, glm::vec2(-5, -5), glm::vec2(30, 30));

  REQUIRE(true);
}