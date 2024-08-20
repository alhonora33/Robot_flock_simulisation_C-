#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <atomic>

namespace robot
{
    class Robot
    {
    public:
        // Constructor with parameters to initialize the robot's ID and position
        Robot(int id, int x, int y) noexcept;

        // Getter methods for the robot's state
        int getId() const noexcept;
        int getX() const noexcept;
        int getY() const noexcept;
        float getBattery() const noexcept;
        float getAngle() const noexcept;

    private:
        int _id; // Unique identifier for the robot

        // Robot's current position, battery level, angle, and running state, all managed atomically
        std::atomic<int> _x; 
        std::atomic<int> _y;
        std::atomic<float> _battery; // Battery level in percentage
        std::atomic<float> _angle; // Angle in degrees
    };
} // namespace robot

#endif // ROBOT_HPP
