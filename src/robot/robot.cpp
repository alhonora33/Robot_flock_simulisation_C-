#include "robot.hpp"

namespace robot
{
    // Constructor
    Robot::Robot(int id, int x, int y) noexcept
        : _id(id), _x(x), _y(y), _battery(100.0f), _angle(0.0f)
    {
    }

    // Getter methods
    int Robot::getId() const noexcept { return _id; }
    int Robot::getX() const noexcept { return _x.load(); }
    int Robot::getY() const noexcept { return _y.load(); }
    float Robot::getBattery() const noexcept { return _battery.load(); }
    float Robot::getAngle() const noexcept { return _angle.load(); }
    
} // namespace robot