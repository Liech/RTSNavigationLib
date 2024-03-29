#include <catch2/catch_test_macros.hpp>

#include <RTSNavigationLib/Util/RectangleGrid/RectangleGrid.h>
#include <RTSNavigationLib/Util/RectangleGrid/RectangleGridSvg.h>
#include <RTSNavigationLib/Util/RectangleGrid/RectangleGridVoxelizer.h>
#include <RTSNavigationLib/Util/svg.h>

namespace RectangleGridTests {
  TEST_CASE("RectangleGrid/voxelizer") {
    glm::ivec2 dimension = glm::ivec2(6, 6);

    std::vector<glm::dvec2> polygon;
    glm::dvec2 offset = glm::dvec2(1, 1);
    double scale = 0.6;
    polygon.push_back(offset + glm::dvec2(1, 0) * scale);
    polygon.push_back(offset + glm::dvec2(0, 4) * scale);
    polygon.push_back(offset + glm::dvec2(4.5, 6) * scale);
    polygon.push_back(offset + glm::dvec2(4, 3) * scale);

    auto t = RTSNavigationLib::RectangleGridVoxelizer::voxelize(polygon, dimension, glm::dvec2(0, 0), 1);
    if (true) {
      RTSNavigationLib::svg v;
      v.streak = polygon;
      v.color = "blue";
      v.thickness = 0.2;
      v.wrapAround = true;
      std::vector<RTSNavigationLib::svg> x = RTSNavigationLib::RectangleGridSvg::write(t, 1);
      x.push_back(v);
      RTSNavigationLib::svg::write("VoxelizerTest.svg", x, glm::dvec2(-5, -5), glm::dvec2(30, 30));
    }

    std::vector<bool> r = {
      false,false,false,false,false,false,
      false,true ,false,false,false,false,
      false,true ,true ,false,false,false,
      false,true ,true ,true ,false,false,
      false,false,false,true ,false,false,
      false,false,false,false,false,false
    };

    REQUIRE(t.data.size() == r.size());
    REQUIRE(t.data == r);
  }

  TEST_CASE("RectangleGrid/or") {
    glm::ivec2 dimension = glm::ivec2(2, 2);
    RTSNavigationLib::RectangleGrid<bool> a;
    a.dimension = dimension;
    a.data.resize(dimension.x * dimension.y);
    RTSNavigationLib::RectangleGrid<bool> b;
    b.dimension = dimension;
    b.data.resize(dimension.x * dimension.y);

    a.data[1] = true;
    a.data[3] = true;
    b.data[2] = true;
    b.data[3] = true;

    auto c = a | b;

    REQUIRE(!c.data[0]);
    REQUIRE(c.data[1]);
    REQUIRE(c.data[2]);
    REQUIRE(c.data[3]);
  }

  TEST_CASE("RectangleGrid/and") {
    glm::ivec2 dimension = glm::ivec2(2, 2);
    RTSNavigationLib::RectangleGrid<bool> a;
    a.dimension = dimension;
    a.data.resize(dimension.x * dimension.y);
    RTSNavigationLib::RectangleGrid<bool> b;
    b.dimension = dimension;
    b.data.resize(dimension.x * dimension.y);

    a.data[1] = true;
    a.data[3] = true;
    b.data[2] = true;
    b.data[3] = true;

    auto c = a & b;

    REQUIRE(!c.data[0]);
    REQUIRE(!c.data[1]);
    REQUIRE(!c.data[2]);
    REQUIRE(c.data[3]);
  }

  TEST_CASE("RectangleGrid/subtract") {
    glm::ivec2 dimension = glm::ivec2(2, 2);
    RTSNavigationLib::RectangleGrid<bool> a;
    a.dimension = dimension;
    a.data.resize(dimension.x * dimension.y);
    RTSNavigationLib::RectangleGrid<bool> b;
    b.dimension = dimension;
    b.data.resize(dimension.x * dimension.y);

    a.data[1] = true;
    a.data[3] = true;
    b.data[2] = true;
    b.data[3] = true;

    auto c = a - b;

    REQUIRE(!c.data[0]);
    REQUIRE(c.data[1]);
    REQUIRE(!c.data[2]);
    REQUIRE(!c.data[3]);
  }
}