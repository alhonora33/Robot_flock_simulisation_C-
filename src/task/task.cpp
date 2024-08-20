#include "task.hpp"

namespace task
{
    Task::Task(int id, int node_id_pick, int node_id_drop) noexcept
        : _id(id), _node_id_pick(node_id_pick), _node_id_drop(node_id_drop), _status(TaskStatus::pending), _assigned_robot_id(-1) {}

    int Task::getId() const noexcept
    {
        return _id;
    }

    int Task::getNodeIdPick() const noexcept
    {
        return _node_id_pick;
    }

    int Task::getNodeIdDrop() const noexcept
    {
        return _node_id_drop;
    }

    TaskStatus Task::getStatus() const noexcept
    {
        return _status;
    }

    int Task::getAssignedRobotId() const noexcept
    {
        return _assigned_robot_id;
    }

    void Task::setStatus(TaskStatus status) noexcept
    {
        _status = status;
    }

    void Task::setAssignedRobotId(int robot_id) noexcept
    {
        _assigned_robot_id = robot_id;
    }

} // namespace task
