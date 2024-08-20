#ifndef TASK_HPP
#define TASK_HPP

#include "graph.hpp"

namespace task
{
    enum class TaskStatus
    {
        pending,
        in_progress,
        done
    };

    class Task
    {
    public:
        // Constructor to initialize Task with IDs and nodes
        Task(int id, int node_id_pick, int node_id_drop) noexcept;

        // Getters for private attributes
        int getId() const noexcept;
        int getNodeIdPick() const noexcept;
        int getNodeIdDrop() const noexcept;
        TaskStatus getStatus() const noexcept;
        int getAssignedRobotId() const noexcept;

        // Setters for task status and assigned robot ID
        void setStatus(TaskStatus status) noexcept;
        void setAssignedRobotId(int robot_id) noexcept;

    private:
        const int _id;           // Unique identifier for the task
        const int _node_id_pick; // Node ID for picking up
        const int _node_id_drop; // Node ID for dropping off
        TaskStatus _status;      // Status of the task
        int _assigned_robot_id;  // ID of the robot assigned to the task (-1 if not assigned)
    };

} // namespace task

#endif // TASK_HPP
