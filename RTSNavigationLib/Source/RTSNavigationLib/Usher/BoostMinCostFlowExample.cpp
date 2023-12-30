#include "BoostMinCostFlowExample.h"

#include <iostream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

namespace RTSPathingLib {
  typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
  typedef Traits::vertex_descriptor vertex_descriptor;

  typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property< boost::edge_capacity_t, long,
    boost::property< boost::edge_residual_capacity_t, long,
    boost::property< boost::edge_reverse_t, Traits::edge_descriptor,
    boost::property< boost::edge_weight_t, long > > > > >
    Graph;
  typedef boost::property_map< Graph, boost::edge_capacity_t >::type          Capacity;
  typedef boost::property_map< Graph, boost::edge_residual_capacity_t >::type ResidualCapacity;
  typedef boost::property_map< Graph, boost::edge_weight_t >::type            Weight;
  typedef boost::property_map< Graph, boost::edge_reverse_t >::type           Reversed;
  typedef boost::graph_traits< Graph >::vertices_size_type                    size_type;

  template < class Graph, class Weight, class Capacity, class Reversed,
    class ResidualCapacity >
  class EdgeAdder
  {
  public:
    EdgeAdder(
      Graph& g, Weight& w, Capacity& c, Reversed& rev, ResidualCapacity&)
      : m_g(g), m_w(w), m_cap(c), m_rev(rev)
    {
    }
    void addEdge(vertex_descriptor v, vertex_descriptor w, long weight,
      long capacity)
    {
      Traits::edge_descriptor e, f;
      e = add(v, w, weight, capacity);
      f = add(w, v, -weight, 0);
      m_rev[e] = f;
      m_rev[f] = e;
    }

  private:
    Traits::edge_descriptor add(vertex_descriptor v, vertex_descriptor w,
      long weight, long capacity)
    {
      bool b;
      Traits::edge_descriptor e;
      boost::tie(e, b) = add_edge(vertex(v, m_g), vertex(w, m_g), m_g);
      if (!b)
      {
        std::cerr << "Edge between " << v << " and " << w
          << " already exists." << std::endl;
        std::abort();
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


  BoostMinCostFlowExample::BoostMinCostFlowExample() {


    vertex_descriptor sourceNode, sinkNode;
    Graph g;

    Capacity capacity = get(boost::edge_capacity, g);
    Reversed rev = get(boost::edge_reverse, g);
    ResidualCapacity residual_capacity = get(boost::edge_residual_capacity, g);
    Weight weight = get(boost::edge_weight, g);

    size_type N(6);

    for (size_type i = 0; i < N; ++i)
    {
      add_vertex(g);
    }

    sourceNode = 0;
    sinkNode = 5;

    EdgeAdder< Graph, Weight, Capacity, Reversed, ResidualCapacity > ea(g, weight, capacity, rev, residual_capacity);

    ea.addEdge(sourceNode, 1, 4, 2);
    ea.addEdge(sourceNode, 2, 2, 2);

    ea.addEdge(1, 3, 2, 2);
    ea.addEdge(1, 4, 1, 1);
    ea.addEdge(2, 3, 1, 1);
    ea.addEdge(2, 4, 1, 1);

    ea.addEdge(3, sinkNode, 4, 20);
    ea.addEdge(4, sinkNode, 2, 20);

    boost::edmonds_karp_max_flow(g, sourceNode, sinkNode);
    boost::cycle_canceling(g);

    int costx = boost::find_flow_cost(g);
    assert(costx == 29);

    typedef typename boost::property_traits< Weight >::value_type Cost;

    Cost cost = 0;
    BGL_FORALL_EDGES_T(e, g, Graph)
    {
      if (get(capacity, e) > Cost(0))
      {
        auto cap      = get(capacity, e);
        auto residual = get(residual_capacity, e);
        auto w        = get(weight, e);
        cost += (cap - residual) * w;
      }
    }
  }
}