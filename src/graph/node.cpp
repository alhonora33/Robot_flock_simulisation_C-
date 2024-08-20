#include "node.hpp"
#include <sstream>

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

    // Method to convert Node data to a JSON string representation
    std::string Node::getToJson() const noexcept
    {
        // Using std::ostringstream for efficient string concatenation
        std::ostringstream json;
        json << "{\n";
        json << "\"id\": " << _id << ",\n";
        json << "\"x\": " << _x << ",\n";
        json << "\"y\": " << _y << ",\n";
        json << "\"p\": ";

        // Convert enum Property to its corresponding string representation
        switch (_prop)
        {
        case Property::node:
            json << "\"node\"";
            break;
        case Property::pickdrop:
            json << "\"pickdrop\"";
            break;
        case Property::waiting:
            json << "\"waiting\"";
            break;
        case Property::charging:
            json << "\"charging\"";
            break;
        default:
            json << "\"unknown\""; // This should never happen, added for safety
            break;
        }

        json << "\n}";
        return json.str();
    }

} // namespace graph