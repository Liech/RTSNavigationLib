#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/Hexagon/TopFlatHexGrid.h>
#include <RTSPathingLib/Hexagon/HexGridSvg.h>

TEST_CASE("Hexagon/wub", "[Hexagon]") {
  TopFlatHexGrid<bool> t;
  HexGridSvg::write("Hello.svg", t);
  REQUIRE(true);
}