#include "tasksmanager.hpp"
#include <sstream>

namespace task
{
    // Constructor with a shared pointer to a Graph object
    TasksManager::TasksManager(std::shared_ptr<graph::Graph> graph) noexcept
        : _graph(graph)
    {
    }

    // Adds random tasks to the task vector based on the number of tasks specified
    void TasksManager::addRandomTasks(int n) noexcept
    {
        for (int i = 0; i < n; ++i)
        {
            int node_id_pick, node_id_drop;

            do
            {
                node_id_pick = _graph->getRandomPickDrop(); // Get a random pick node
                node_id_drop = _graph->getRandomPickDrop(); // Get a random drop node
            } while (node_id_pick == node_id_drop || node_id_pick == -1 || node_id_drop == -1); // Ensure pick and drop nodes are different and not 0

            _tasks.emplace_back(_task_id++, node_id_pick, node_id_drop);
        }
    }

    // Returns a reference to the tasks vector
    std::vector<Task> &TasksManager::getTasks() noexcept
    {
        return _tasks;
    }

    // Clears all tasks
    void TasksManager::clear() noexcept
    {
        _tasks.clear();
    }

    // Returns a JSON string with all tasks
    std::string TasksManager::getToJson() const noexcept
    {
        std::ostringstream json;

        json << "{\n\"tasks\": [\n";

        for (std::size_t i = 0; i < _tasks.size(); ++i)
        {
            json << _tasks[i].getToJson();
            if (i < _tasks.size() - 1) // Add a comma unless it's the last element
            {
                json << ",";
            }
            json << "\n";
        }

        json << "]\n}";
        return json.str();
    }

} // namespace task