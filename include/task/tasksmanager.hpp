#ifndef TASKSMANAGER_HPP
#define TASKSMANAGER_HPP

#include "task.hpp"
#include <memory>
#include <vector>

namespace task
{
    class TasksManager
    {
    public:
        // Constructor with a shared pointer to a Graph object
        TasksManager(std::shared_ptr<graph::Graph> graph) noexcept;

        // Adds random tasks
        void addRandomTasks(int n) noexcept;

        // Returns a reference to the tasks
        std::vector<Task> &getTasks() noexcept;

        // Clears all tasks
        void clear() noexcept;

    private:
        std::vector<Task> _tasks;             // Vector holding all tasks
        std::shared_ptr<graph::Graph> _graph; // Graph reference
        int _task_id = 0;                     // Task ID counter
    };
} // namespace task

#endif // TASKSMANAGER_HPP
