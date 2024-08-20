#include "robot.hpp"
#include <cmath>
#include <sstream>
namespace robot
{
    // Constructor
    Robot::Robot(int id, int x, int y) noexcept
        : _id(id), _x(x), _y(y), _battery(100.0f), _angle(0.0f), _running(false)
    {
        _worker_thread = std::thread(&Robot::_workerFunction, this); // Start the worker thread
    }
    // Destructor
    Robot::~Robot() noexcept
    {
        stop();
    }

    // Stops the robot's execution and safely shuts down the thread
    void Robot::stop() noexcept
    {
        _running = false; // Signal the worker thread to stop
        _cv.notify_all(); // Wake up the worker thread if it's waiting
        if (_worker_thread.joinable())
        {
            _worker_thread.join(); // Wait for the worker thread to finish
        }
    }

    // Getter methods
    int Robot::getId() const noexcept { return _id; }
    int Robot::getX() const noexcept { return _x.load(); }
    int Robot::getY() const noexcept { return _y.load(); }
    float Robot::getBattery() const noexcept { return _battery.load(); }
    float Robot::getAngle() const noexcept { return _angle.load(); }

    // Adds a movement task to the queue
    void Robot::move(int x, int y) noexcept
    {
        _addTask([this, x, y]()
                 {
            int dx = (x > _x) ? 1 : (x < _x) ? -1 : 0;
            int dy = (y > _y) ? 1 : (y < _y) ? -1 : 0;

            while (_x != x || _y != y)
            {
                if (_x != x)
                {
                    _x += dx;
                }
                if (_y != y)
                {
                    _y += dy;
                }
                _angle = std::atan2(dy, dx) * 180.0 / M_PI; // Update the angle
                _battery -= MOVE_BATTERY_CONSUMPTION; // Consume battery
                std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
            } });
    }

    // Marks the given task as done after executing all moves
    void Robot::markTaskDone(task::Task *task) noexcept
    {
        _addTask([task]()
                 { task->setStatus(task::TaskStatus::done); });
    }

    // Adds a task to the queue
    void Robot::_addTask(const std::function<void()> &task) noexcept
    {
        {
            std::lock_guard<std::mutex> lock(_queue_mutex);
            _robot_task_queue.push(task);
        }
        _cv.notify_one();
    }

    // Executes tasks in the queue
    void Robot::executeTasks() noexcept
    {
        while (_running)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(_queue_mutex);
                _cv.wait(lock, [this]
                         { return !_robot_task_queue.empty() || !_running; });

                if (!_running && _robot_task_queue.empty())
                    break;

                task = _robot_task_queue.front();
                _robot_task_queue.pop();
            }

            if (task)
            {
                task();
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(NO_TASK_WAIT_TIME)); // Sleep for 100 milliseconds
            }
        }
    }

    bool Robot::isAvailable() noexcept
    {
        std::lock_guard<std::mutex> lock(_queue_mutex);
        return _robot_task_queue.empty() && _running;
    }

    // Worker thread function
    void Robot::_workerFunction() noexcept
    {
        while (_running)
        {
            executeTasks(); // Continuously execute tasks
        }
    }

    // Convert robot's state to JSON format
    std::string Robot::getToJson() const noexcept
    {
        std::ostringstream json;
        json << "{\n";
        json << "\"id\": " << _id << ",\n";
        json << "\"x\": " << _x.load() << ",\n";
        json << "\"y\": " << _y.load() << ",\n";
        json << "\"battery\": " << _battery.load() << ",\n";
        json << "\"angle\": " << _angle.load() << "\n";
        json << "}";
        return json.str();
    }

} // namespace robot