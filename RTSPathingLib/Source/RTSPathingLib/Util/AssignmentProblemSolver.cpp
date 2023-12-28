#include "AssignmentProblemSolver.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

namespace RTSPathingLib {
  std::vector<size_t> AssignmentProblemSolverPlain::getTickets(const std::map<std::pair<size_t, size_t>, double>& allCosts) {
    std::vector<size_t> result;

    return result;
  }
}