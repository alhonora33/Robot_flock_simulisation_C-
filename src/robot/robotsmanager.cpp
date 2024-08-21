#include "robotsmanager.hpp"
#include <chrono>
#include <sstream>

namespace robot
{
    // Constructor with parameters to initialize the RobotsManager with a graph and a task manager
    RobotsManager::RobotsManager(std::shared_ptr<graph::Graph> graph, std::shared_ptr<task::TasksManager> tasks_manager) noexcept
        : _graph(graph), _tasks_manager(tasks_manager), _running(true)
    {
    }

    // Adds a new robot to the manager
    void RobotsManager::addRobot(float x, float y) noexcept
    {
        _robots.emplace_back(std::make_shared<Robot>(_id_robot++, x, y));
    }

    // Clears all robots from the manager
    void RobotsManager::clear() noexcept
    {
        _running = false; // Signal the allocation loop to stop
        stopAllRobots();  // Stop all robots before clearing the list
        _robots.clear();  // Clear the robots list
        _id_robot = 0;    // Reset robot ID counter
    }

    // Assigns tasks to robots and manages their execution
    void RobotsManager::assignAndExecuteTasks() noexcept
    {
        _running = true; // Ensure the loop can run
        while (_running)
        {
            task::Task *pending_task = nullptr;

            // Search for a pending task
            for (auto &t : _tasks_manager->getTasks())
            {
                if (t.getStatus() == task::TaskStatus::pending)
                {
                    pending_task = &t; // A pending task found, remove const to modify task status
                    break;
                }
            }

            if (pending_task == nullptr)
            {
                // No pending task found, wait before checking again
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            // Find an available robot
            for (auto &robot : _robots)
            {
                if (robot->isAvailable())
                {
                    // Update the task status and assign it to the robot
                    pending_task->setStatus(task::TaskStatus::in_progress);
                    pending_task->setAssignedRobotId(robot->getId());

                    int start_node = _graph->getNodeAt(robot->getX(), robot->getY());
                    int pick_node = pending_task->getNodeIdPick();
                    int dropNode = pending_task->getNodeIdDrop();

                    // Move towards the pick-up point
                    auto path_to_pick = _graph->getShortestPath(start_node, pick_node);
                    for (int node : path_to_pick)
                    {
                        const auto &node_position = _graph->getNode(node);
                        robot->move(node_position.getX(), node_position.getY());
                    }

                    // Move towards the drop-off point
                    auto path_to_drop = _graph->getShortestPath(pick_node, dropNode);
                    for (int node : path_to_drop)
                    {
                        const auto &node_position = _graph->getNode(node);
                        robot->move(node_position.getX(), node_position.getY());
                    }

                    // Instruct the robot to mark the task as completed
                    robot->markTaskDone(pending_task);

                    break; // Exit the loop after assigning the task
                }
            }
        }
    }

    void RobotsManager::stopAllRobots() noexcept
    {
        for (auto &robot : _robots)
        {
            robot->stop(); // Safely stop each robot
        }
    }

    std::string RobotsManager::getToJson() const noexcept
    {
        std::ostringstream json;
        json << "{\n\"robots\": [\n";

        for (std::size_t i = 0; i < _robots.size(); ++i)
        {
            json << _robots[i]->getToJson();
            if (i < _robots.size() - 1) // Add a comma unless it's the last element in the list
            {
                json << ",";
            }
            json << "\n";
        }

        json << "]\n}\n";
        return json.str();
    }

} // namespace robot
