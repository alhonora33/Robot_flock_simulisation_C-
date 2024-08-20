#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "task.hpp"
#include <string>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <string>

#define NO_TASK_WAIT_TIME 100 // Check for new tasks every 0.1 second if no tasks are available

#define SPEED 40 // 1 pixel per 40 milliseconds => 1 SCALE unit per 2 seconds

#define MOVE_BATTERY_CONSUMPTION 0.1f // Battery consumption per move

namespace robot
{
    class Robot
    {
    public:
        // Constructor with parameters to initialize the robot's ID and position
        Robot(int id, int x, int y) noexcept;

        // Destructor to stop the robot's execution
        ~Robot() noexcept;

        // Stops the robot's execution and safely shuts down the thread
        void stop() noexcept;

        // Getter methods for the robot's state
        int getId() const noexcept;
        int getX() const noexcept;
        int getY() const noexcept;
        float getBattery() const noexcept;
        float getAngle() const noexcept;

        // A method to check if the robot is running
        bool isAvailable() noexcept;

        // Adds a move task to the robot's task queue
        void move(int x, int y) noexcept;

        // Marks the given task as done after executing all moves
        void markTaskDone(task::Task* task) noexcept;

        // Executes tasks in the robot's task queue
        void executeTasks() noexcept;

        // Method to get a JSON representation of the robot's state
        std::string getToJson() const noexcept;

    private:
        int _id; // Unique identifier for the robot

        // Robot's current position, battery level, angle, and running state, all managed atomically
        std::atomic<int> _x;
        std::atomic<int> _y;
        std::atomic<float> _battery; // Battery level in percentage
        std::atomic<float> _angle;   // Angle in degrees
        std::atomic<bool> _running;  // Flag to control the robot's running state

        std::queue<std::function<void()>> _robot_task_queue; // Queue of tasks for the robot
        std::mutex _queue_mutex;                             // Mutex to protect the task queue
        std::condition_variable _cv;                         // Condition variable to notify the worker thread of new tasks

        std::thread _worker_thread; // Thread that processes tasks in the task queue

        // Private function that defines the worker thread's behavior
        void _workerFunction() noexcept;

        // Adds a task to the robot's task queue
        void _addTask(const std::function<void()> &task) noexcept;
    };
} // namespace robot

#endif // ROBOT_HPP
