#include "node.hpp"

namespace graph
{
    // Constructor initializing all member variables
    Node::Node(int id, int x, int y, const Property &prop) noexcept
        : _id(id), _x(x), _y(y), _prop(prop)
    {
    }

    // Getter method for _id
    int Node::getId() const noexcept
    {
        return _id;
    }

    // Getter method for _x
    int Node::getX() const noexcept
    {
        return _x;
    }

    // Getter method for _y
    int Node::getY() const noexcept
    {
        return _y;
    }

    // Getter method for _prop (Property)
    Property Node::getProperty() const noexcept
    {
        return _prop;
    }

} // namespace graph