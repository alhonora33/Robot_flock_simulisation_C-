#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "node.hpp"
#include <vector>
#include <memory>

namespace graph
{
    class Graph
    {
    public:
        // Retrieves the node by its index
        const Node &getNode(int i) const noexcept;

        // Checks if there's an edge between nodes i and j
        int isEdge(int i, int j) const noexcept;

   
        // Adds a node to the graph
        void addNode(int id, int x, int y, const Property &prop) noexcept;

        // Adds an edge between nodes
        void addEdge(int node_1, int node_2) noexcept;

        // Clears the graph
        void clear() noexcept;

    private:
        std::vector<std::unique_ptr<Node>> _nodes; // Vector holding all nodes
        std::vector<std::vector<int>> _edges;      // Adjacency matrix representing edges
    };
} // namespace graph

#endif // GRAPH_HPP