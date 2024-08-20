#include "graph.hpp"
#include <random>
namespace graph
{
  // Clears the nodes and edges of the graph
  void Graph::clear() noexcept
  {
    _nodes.clear();
    _edges.clear();
    _pickdropNodes.clear();
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

  // Returns a random pick-drop node index
  int Graph::getRandomPickDrop() const noexcept
  {
    if (_pickdropNodes.size() < 2)
    {
      return -1; // Return -1 if there are less than 2 pick-drop nodes
    }

    std::random_device rd; // Random seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(0, _pickdropNodes.size() - 1); // Uniform distribution

    return _pickdropNodes[dist(gen)]; // Return a random pick-drop node index
  }

  // Adds a node to the graph and updates the adjacency matrix
  void Graph::_addNode(int id, int x, int y, const Property &prop) noexcept
  {
    _nodes.emplace_back(std::make_unique<Node>(id, x, y, prop));

    if (prop == Property::pickdrop)
    {
      _pickdropNodes.push_back(_nodes.size() - 1); // Add the index of the pickdrop node
    }

    for (auto &edge : _edges)
    {
      edge.push_back(0);
    }
    _edges.emplace_back(_nodes.size(), 0);
  }
  // Adds an edge between two nodes (bidirectional)
  void Graph::_addEdge(int i, int j) noexcept
  {
    _edges[i][j] = 1;
    _edges[j][i] = 1;
  }

} // namespace graph
