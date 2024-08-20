#ifndef NODE_HPP
#define NODE_HPP

#include <string>

namespace graph
{
    enum class Property
    {
        node,
        pickdrop,
        waiting,
        charging
    };

    class Node
    {
    public:
        Node(int id, int x, int y, const Property &prop) noexcept;

        // Getter methods for private member variables
        int getId() const noexcept;
        int getX() const noexcept;
        int getY() const noexcept;
        Property getProperty() const noexcept;

        // Methode to convert Node data to a JSON string representation
        std::string getToJson() const noexcept;

    private:
        const int _id;
        const int _x;
        const int _y;
        const Property _prop;
    };
} // namespace graph

#endif // NODE_HPP