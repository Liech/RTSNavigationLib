#include "UnitPlacement.h"

#include "Body.h"

namespace RTSPathingLib {
  UnitPlacement::UnitPlacement(RectangleGrid<bool>& unitGrid, const std::map<size_t, size_t>& unitList, size_t category_) : 
  grid(unitGrid),
  unitsToPlace(unitList){
    category = category_;
  }

  std::vector<Body> UnitPlacement::place(bool& success) const {
    success = false;

    std::vector<Body> result;

    for (const auto& x : unitsToPlace) {
      size_t size = x.first;
      if (size == 1)
        continue;
      auto sub = placeSizeN(size, unitsToPlace.at(size), success);
      if (!success)
        return {};
      result.insert(result.begin(), sub.begin(), sub.end());
    }

    if (unitsToPlace.count(1) != 0) {
      auto size1 = placeSize1(success);
      if (!success)
        return {};
      result.insert(result.begin(), size1.begin(), size1.end());
    }

    success = true;
    return result;
  }

  std::vector<Body> UnitPlacement::placeSizeN(size_t size, size_t amount, bool& success) const {
    std::vector<Body> result;

    RectangleGrid<bool> possiblePlaces = grid;
    auto get = [this](const glm::ivec2& pos){return grid.data[pos.x+pos.y* grid.dimension.x]; };
    for (size_t i = 0; i < grid.data.size(); i++) {
      if (!grid.data[i] || !possiblePlaces.data[i])
        continue;
      glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, i / grid.dimension.x);
      bool ok = true;
      for (size_t x = 0; x < size; x++)
        for (size_t y = 0; y < size; y++) {
          bool inBoundX = x + pos.x < grid.dimension.x;
          bool inBoundY = y + pos.y < grid.dimension.y;
          ok &= inBoundX&&inBoundY&&get(pos + glm::ivec2(x, y));
        }
      if (ok) {
        for (size_t x = 0; x < size && x + pos.x < grid.dimension.x; x++)
          for (size_t y = 0; y < size && y + pos.y < grid.dimension.y; y++) {
            possiblePlaces.data[(pos.x+x) + (pos.y+y) * grid.dimension.x] = false;
          }
      }
      possiblePlaces.data[i] = ok;
    }
    auto possible = getAllPlaces(possiblePlaces);
    if (possible.size() < amount) {
      success = false;      
      return {};
    }
    for (size_t i = 0; i < amount; i++) {
      Body sub;
      sub.category = category;
      sub.size = size;
      sub.position = (glm::dvec2)possible[i] + (glm::dvec2)grid.offset + glm::dvec2(0.5, 0.5);
      result.push_back(sub);
    }


    success = true;
    return result;
  }

  std::vector<glm::ivec2> UnitPlacement::getAllPlaces(const RectangleGrid<bool>& places) const {
    std::vector<glm::ivec2> result;
    for (size_t i = 0; i < places.data.size(); i++) {
      if (places.data[i])
        result.push_back(glm::ivec2(i % places.dimension.x, i / places.dimension.x));
    }
    return result;
  }

  std::vector<Body> UnitPlacement::placeSize1(bool& success) const {
    std::vector<Body> result;
    size_t currentSize = 1;
    RectangleGrid<bool> actuallyPlaced;
    actuallyPlaced.dimension = grid.dimension;
    actuallyPlaced.offset = grid.offset;
    actuallyPlaced.data.resize(grid.data.size());
    long long amountUnits = (long long)unitsToPlace.at(currentSize);
    for (size_t i = 0; i < grid.data.size() && amountUnits>0; i++) {
      if (grid.data[i]) {
        glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, (i / grid.dimension.x) % grid.dimension.y);
        Body sub;
        sub.category = category;
        sub.size = currentSize;
        sub.position = (glm::dvec2)pos + (glm::dvec2)grid.offset + glm::dvec2(0.5, 0.5);
        result.push_back(sub);
        actuallyPlaced.data[i] = true;
        amountUnits--;
      }
    }
    if (amountUnits <= 0)
      success = true;
    grid = actuallyPlaced;
    return result;
  }
}