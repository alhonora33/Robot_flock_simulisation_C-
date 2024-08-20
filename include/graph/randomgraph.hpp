        #ifndef RANDOMGRAPH_HPP
        #define RANDOMGRAPH_HPP

        #include "graph.hpp"
        #include <array>

        #define CONNECTIVITY 3 // 33.33% connectivity between normal nodes
        #define SCALE 50 // 50 pixels between nodes

        namespace graph
        {
            enum class Direction
            {
                up,
                right,
                down,
                left,
                num_directions
            };

            class RandomGraph : public Graph
            {
            public:
                // Constructor to initialize the random graph
                RandomGraph() noexcept;

                // Generates a random graph with the specified number of nodes
                void genRandomGraph(int num_node, int num_waiting, int num_charging, int num_pickdrop) noexcept;

            private:
                // Number of different types of nodes in the graph
                int _num_node;
                int _num_waiting;
                int _num_charging;
                int _num_pickdrop;

                int _id_node;        // Unique identifier for nodes
                int _current_node;   // Currently active node during generation
                int _from_direction; // Direction from which the current node was entered

                std::array<bool, static_cast<int>(Direction::num_directions)> _tested_directions; // Tracks tested directions

                // Finds the node at the specified (x, y) coordinates
                int _getNodeAt(int x, int y) const noexcept;

                // Resets the direction test array
                inline void _clearTestedDirections() noexcept;

                // Calculates new coordinates based on the direction
                static inline std::pair<int, int> _getNewCoordinates(int x, int y, Direction direction) noexcept;
            };
        } // namespace graph

        #endif // RANDOMGRAPH_HPP
