#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/Hexagon/TopFlatHexGrid.h>
#include <RTSPathingLib/Hexagon/HexGridSvg.h>

TEST_CASE("Hexagon/wub", "[Hexagon]") {
  TopFlatHexGrid<bool> t;
  t.dimension = glm::ivec2(5, 5);
  t.data.resize(25);
  t.data[3] = true;
  t.data[5] = true;
  t.data[9] = true;
  HexGridSvg::write("Hello.svg", t);
  REQUIRE(true);
}