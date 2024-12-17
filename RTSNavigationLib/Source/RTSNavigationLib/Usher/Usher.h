#pragma once

#include <memory>
#include <vector>

namespace RTSNavigationLib
{
    struct WorldBody;
    class RTree2D;

    class Usher
    {
      public:
        Usher();
        static std::vector<size_t> assignPlaces(const std::vector<WorldBody>& units, const std::vector<WorldBody>& places);
        static std::vector<size_t> assignPlaces2KD(const std::vector<WorldBody>& units, const std::vector<WorldBody>& places);
        static std::vector<size_t> assignPlacesMCF(const std::vector<WorldBody>& units, const std::vector<WorldBody>& places);

        static void visualize(const std::vector<size_t>& usherResult, const std::vector<WorldBody>& units, const std::vector<WorldBody>& places);

      private:
    };
}