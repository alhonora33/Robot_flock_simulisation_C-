#include "randomgraph.hpp"
#include <random>
#include <algorithm>
#include <iterator>

namespace graph
{
    // Constructor: Initializes random seed and clears the graph
    RandomGraph::RandomGraph() noexcept
        : Graph()
    {
        std::random_device rd;    // Random seed
        std::mt19937 gen(rd());   // Mersenne Twister engine
        _id_node = 0;             // Initialize node identifier
        _current_node = 0;        // Initialize current node
        _from_direction = -1;     // Initialize direction
        _clearTestedDirections(); // Clear tested directions
        clear();                  // Clear the graph
    }

    // Retrieves the node at the specified (x, y) coordinates
    int RandomGraph::_getNodeAt(int x, int y) const noexcept
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

    // Resets the array that tracks tested directions
    inline void RandomGraph::_clearTestedDirections() noexcept
    {
        std::fill(_tested_directions.begin(), _tested_directions.end(), false);
    }

    // Computes new coordinates based on the current position and direction
    inline std::pair<int, int> RandomGraph::_getNewCoordinates(int x, int y, Direction direction) noexcept
    {
        switch (direction)
        {
        case Direction::up:
            y -= SCALE;
            break;
        case Direction::right:
            x += SCALE;
            break;
        case Direction::down:
            y += SCALE;
            break;
        case Direction::left:
            x -= SCALE;
            break;
        default:
            break;
        }
        return {x, y};
    }

    // Generates a random graph with specified node quantities
    void RandomGraph::genRandomGraph(int num_node, int num_waiting, int num_charging, int num_pickdrop) noexcept
    {
        _num_node = num_node;
        _num_waiting = num_waiting;
        _num_charging = num_charging;
        _num_pickdrop = num_pickdrop;
        clear();                  // Clear the graph
        _id_node = 0;             // Initialize node identifier
        _current_node = 0;        // Initialize current node
        _from_direction = -1;     // Initialize direction
        _clearTestedDirections(); // Clear tested directions

        // Initialize the first pickdrop node
        Graph::addNode(_id_node++, 0, 0, Property::pickdrop);
        _num_pickdrop--;

        // Initialize the first normal node and edge
        Graph::addNode(_id_node++, 0, SCALE, Property::node);
        _num_node--;
        Graph::addEdge(0, 1);

        _current_node = 1;                                            // Set the current node to the first normal node
        _tested_directions[static_cast<int>(Direction::down)] = true; // Mark the direction down as tested
        _from_direction = -1;

        // Generate the rest of the graph
        while (_num_node > 0 && (_num_charging > 0 || _num_waiting > 0 || _num_pickdrop > 0)) // While there are nodes to create
        {
            // If all directions have been tested, backtrack or stop
            if (std::all_of(_tested_directions.begin(), _tested_directions.end(), [](bool tested)
                            { return tested; }))
            {
                if (_from_direction == -1)
                {
                    break; // No way to backtrack, so break
                }
                else
                {
                    // Backtrack to the previous node
                    auto [prev_x, prev_y] = _getNewCoordinates(getNode(_current_node).getX(), getNode(_current_node).getY(), static_cast<Direction>(_from_direction));
                    _clearTestedDirections();
                    _tested_directions[(_from_direction + 2) % 4] = true; // Mark the opposite direction as tested
                    _current_node = _getNodeAt(prev_x, prev_y);
                    _from_direction = -1;
                    continue;
                }
            }

            // Select a random untested direction
            int new_direction;
            while (true)
            {
                new_direction = std::rand() % 4;
                if (!_tested_directions[new_direction])
                {
                    break;
                }
            }

            _tested_directions[new_direction] = true;
            auto [new_x, new_y] = _getNewCoordinates(getNode(_current_node).getX(), getNode(_current_node).getY(), static_cast<Direction>(new_direction));

            int node = _getNodeAt(new_x, new_y);

            if (node == -1) // No node exists at new coordinates, create one
            {
                int r = std::rand() % (_num_node + _num_charging + _num_waiting + _num_pickdrop);

                if (r < _num_node) // Create a normal node
                {
                    if (_num_node == 1) // Last normal node, create a pickdrop node
                    {
                        addNode(_id_node++, new_x, new_y, Property::pickdrop);
                        _num_node--;
                        addEdge(_current_node, _id_node - 1);
                        break; // No more nodes to create
                    }
                    else // Create a normal node
                    {
                        addNode(_id_node++, new_x, new_y, Property::node);
                        _num_node--;
                        addEdge(_current_node, _id_node - 1);
                        _current_node = _id_node - 1;
                        _from_direction = (new_direction + 2) % 4;
                        _clearTestedDirections();
                        _tested_directions[_from_direction] = true;
                    }
                }
                else if (r < _num_node + _num_charging) // Create a charging node
                {
                    addNode(_id_node++, new_x, new_y, Property::charging);
                    _num_charging--;
                    addEdge(_current_node, _id_node - 1);
                }
                else if (r < _num_node + _num_charging + _num_waiting) // Create a waiting node
                {
                    addNode(_id_node++, new_x, new_y, Property::waiting);
                    _num_waiting--;
                    addEdge(_current_node, _id_node - 1);
                }
                else // Create a pickdrop node
                {
                    addNode(_id_node++, new_x, new_y, Property::pickdrop);
                    _num_pickdrop--;
                    addEdge(_current_node, _id_node - 1);
                }
            }
            else // Node exists at new coordinates
            {
                if (getNode(node).getProperty() == Property::node && isEdge(_current_node, node) == 1) // Node is a normal node and is connected
                {
                    _current_node = node;
                    _clearTestedDirections();
                    _tested_directions[(new_direction + 2) % 4] = true;
                    _from_direction = -1;
                }
                else if (getNode(node).getProperty() == Property::node && isEdge(_current_node, node) == 0) // Node is a normal node but is not connected
                {
                    if (!(std::rand() % CONNECTIVITY))
                        addEdge(_current_node, node);
                    _tested_directions[new_direction] = true;
                }
                else // Node is not a normal node
                {
                    _tested_directions[new_direction] = true;
                }
            }
        }
    }
} // namespace graph