#include "graph.hpp"
#include <random>
#include <algorithm>
#include <queue>
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

  // Retrieves the node at the specified (x, y) coordinates
  int Graph::getNodeAt(int x, int y) const noexcept
  {
    auto it = std::find_if(_nodes.cbegin(), _nodes.cend(),
                           [x, y](const std::unique_ptr<Node> &node)
                           {
                             return node->getX() == x && node->getY() == y;
                           });
    if (it != _nodes.cend())
    {
      return std::distance(_nodes.cbegin(), it);
    }
    return -1;
  }

  // Finds the shortest path between two nodes using BFS
  std::vector<int> Graph::getShortestPath(int i, int j) const noexcept
  {
    std::vector<int> path;
    std::vector<int> visited(_nodes.size(), 0);
    std::vector<int> pred(_nodes.size(), -1);
    std::queue<int> queue;

    queue.push(i);
    visited[i] = 1;

    // BFS to find the shortest path
    while (!queue.empty())
    {
      int node = queue.front();
      queue.pop();

      for (std::size_t k = 0; k < _edges[node].size(); ++k)
      {
        if (_edges[node][k] == 1 && visited[k] == 0)
        {
          visited[k] = 1;
          pred[k] = node;
          queue.push(static_cast<int>(k));

          // Stop if we reached the destination
          if (static_cast<int>(k) == j)
          {
            break;
          }
        }
      }
    }

    // Trace the path back from the destination to the source
    int node = j;
    while (node != -1)
    {
      path.push_back(node);
      node = pred[node];
    }

    std::reverse(path.begin(), path.end());
    return path;
  }

  // Returns a random pick-drop node index
  int Graph::getRandomPickDrop() const noexcept
  {
    if (_pickdropNodes.size() < 2)
    {
      return -1; // Return -1 if there are less than 2 pick-drop nodes
    }

    std::random_device rd;                                              // Random seed
    std::mt19937 gen(rd());                                             // Mersenne Twister engine
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
