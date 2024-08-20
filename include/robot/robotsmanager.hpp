#ifndef ROBOTSMANAGER_HPP
#define ROBOTSMANAGER_HPP

#include "robot.hpp"
#include "graph.hpp"
#include "tasksmanager.hpp"
#include <memory>
#include <vector>
#include <string>

namespace robot
{
    class RobotsManager
    {
    public:
        // Constructor with parameters to initialize the RobotsManager with a graph and a task manager
        RobotsManager(std::shared_ptr<graph::Graph> graph, std::shared_ptr<task::TasksManager> tasks_manager) noexcept;

        // Adds a new robot to the manager
        void addRobot(float x, float y) noexcept;

        // Clears all robots from the manager
        void clear() noexcept;

        // Assigns tasks to robots and manages their execution
        void assignAndExecuteTasks() noexcept;

        // Stops all robots in the manager
        void stopAllRobots() noexcept;

        // Method to get a JSON representation of the robots
        std::string getToJson() const noexcept;

    private:
        std::shared_ptr<graph::Graph> _graph; // Shared pointer to the graph object
        std::shared_ptr<task::TasksManager> _tasks_manager; // Shared pointer to the task manager object
        std::vector<std::shared_ptr<Robot>> _robots; // Vector holding all managed robots
        int _id_robot = 0; // Counter for robot IDs
        bool _running; // Flag to control the main loop
    };
} // namespace robot

#endif // ROBOTSMANAGER_HPP
