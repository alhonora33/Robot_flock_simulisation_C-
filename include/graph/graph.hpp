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

        // Returns a random pick-drop node index
        int getRandomPickDrop() const noexcept;

        // Clears the graph
        void clear() noexcept;

    protected:
        std::vector<std::unique_ptr<Node>> _nodes; // Vector holding all nodes, needs to be protected for derived classes

        // Adds a node to the graph
        void _addNode(int id, int x, int y, const Property &prop) noexcept;

        // Adds an edge between nodes
        void _addEdge(int node_1, int node_2) noexcept;

    private:
        std::vector<std::vector<int>> _edges; // Adjacency matrix representing edges
        std::vector<int> _pickdropNodes;      // Vector holding indices of pickdrop nodes
    };
} // namespace graph

#endif // GRAPH_HPP