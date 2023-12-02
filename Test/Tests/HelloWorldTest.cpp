#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/HelloWorld.h>

TEST_CASE("HelloWorldTest", "[HelloWorld]") {
  HelloWorld h;
  REQUIRE(h.getMessage() == "Hello World");
}