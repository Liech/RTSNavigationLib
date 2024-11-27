#include "AssignmentProblemSolver.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/boykov_kolmogorov_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef Traits::vertex_descriptor vertex_descriptor;

typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property< boost::edge_capacity_t, long,
  boost::property< boost::edge_residual_capacity_t, long,
  boost::property< boost::edge_reverse_t, Traits::edge_descriptor,
  boost::property< boost::edge_weight_t, double > > > > >
  Graph;
typedef boost::property_map< Graph, boost::edge_capacity_t >::type          Capacity;
typedef boost::property_map< Graph, boost::edge_residual_capacity_t >::type ResidualCapacity;
typedef boost::property_map< Graph, boost::edge_weight_t >::type            Weight;
typedef boost::property_map< Graph, boost::edge_reverse_t >::type           Reversed;
typedef boost::graph_traits< Graph >::vertices_size_type                    size_type;

template < class Graph, class Weight, class Capacity, class Reversed, class ResidualCapacity >
class EdgeAdder
{
public:
  EdgeAdder(Graph& g, Weight& w, Capacity& c, Reversed& rev, ResidualCapacity&)
    : m_g(g), m_w(w), m_cap(c), m_rev(rev)
  {
  }
  void addEdge(vertex_descriptor v, vertex_descriptor w, double weight, long capacity)
  {
    Traits::edge_descriptor e, f;
    e = add(v, w, weight, capacity);
    f = add(w, v, -weight, 0);
    m_rev[e] = f;
    m_rev[f] = e;
  }

private:
  Traits::edge_descriptor add(vertex_descriptor v, vertex_descriptor w, double weight, long capacity)
  {
    bool b;
    Traits::edge_descriptor e;
    boost::tie(e, b) = add_edge(vertex(v, m_g), vertex(w, m_g), m_g);
    if (!b)
    {
      throw std::runtime_error("Edge already exists");
    }
    m_cap[e] = capacity;
    m_w[e] = weight;
    return e;
  }

  Graph& m_g;
  Weight& m_w;
  Capacity& m_cap;
  Reversed& m_rev;
};

namespace RTSNavigationLib {

  std::vector<size_t> AssignmentProblemSolverPlain::getTickets(size_t workerAmount, const std::map<std::pair<size_t, size_t>, double>& allCosts) {
    //jobAmount == workerAmount
    std::vector<size_t> result;

    //double maxCost = -std::numeric_limits<double>::infinity();
    //for (auto& c : allCosts)
    //  maxCost = std::max(maxCost, c.second);

    vertex_descriptor sourceNode, sinkNode;
    Graph g;

    Capacity capacity = get(boost::edge_capacity, g);
    Reversed rev = get(boost::edge_reverse, g);
    ResidualCapacity residual_capacity = get(boost::edge_residual_capacity, g);
    Weight weight = get(boost::edge_weight, g);


    size_type N(workerAmount*2+2);
    for (size_type i = 0; i < N; ++i){
      add_vertex(g);
    }

    sourceNode = N-2;
    sinkNode   = N-1;

    EdgeAdder< Graph, Weight, Capacity, Reversed, ResidualCapacity > ea(g, weight, capacity, rev, residual_capacity);

    //source and sink connections
    for (size_t i = 0; i < workerAmount; i++) {
      ea.addEdge(sourceNode, i, 1, 1);
      ea.addEdge(workerAmount+i, sinkNode, 1, 1);
    }

    //connect everything with everything
    for (size_t dude = 0; dude < workerAmount; dude++) {
      for (size_t job = 0; job < workerAmount; job++) {
        ea.addEdge(dude, job + workerAmount, allCosts.at(std::pair<size_t,size_t>(dude,job)), 1);
      }
    }


    //boost::edmonds_karp_max_flow(g, sourceNode, sinkNode); // slow
    //boost::boykov_kolmogorov_max_flow(g, sourceNode, sinkNode);
    boost::push_relabel_max_flow(g, sourceNode, sinkNode);
    boost::cycle_canceling(g);

    result.resize(workerAmount);
    BGL_FORALL_EDGES_T(e, g, Graph)
    {
      auto cap = get(capacity, e);
      auto residual = get(residual_capacity, e);
      auto w = get(weight, e);
      if (residual == 0 && e.m_source < workerAmount && e.m_target != sourceNode) //edge is used and source is worker node
        result[e.m_source] = e.m_target - workerAmount;
    }

    return result;
  }
}