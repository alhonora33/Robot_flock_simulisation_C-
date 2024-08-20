#include "graph.hpp"

namespace graph
{
  // Clears the nodes and edges of the graph
  void Graph::clear() noexcept
  {
    _nodes.clear();
    _edges.clear();
  }

  // Checks if there is an edge between two nodes
  int Graph::isEdge(int i, int j) const noexcept
  {
    return _edges[i][j];
  }

  // Returns a constant reference to a node by index
  const Node &Graph::getNode(int i) const noexcept
  {
    return *(_nodes[i]);
  }

  // Adds a node to the graph and updates the adjacency matrix
  void Graph::addNode(int id, int x, int y, const Property &prop) noexcept
  {
    _nodes.emplace_back(std::make_unique<Node>(id, x, y, prop));
    for (auto &edge : _edges)
    {
      edge.push_back(0);
    }
    _edges.emplace_back(_nodes.size(), 0);
  }

  // Adds an edge between two nodes (bidirectional)
  void Graph::addEdge(int i, int j) noexcept
  {
    _edges[i][j] = 1;
    _edges[j][i] = 1;
  }

} // namespace graph
