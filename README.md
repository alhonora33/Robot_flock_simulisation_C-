# CMR Optimisation App (C++)

This project is a simulation framework for optimizing coalescent mobile robotics tasks. The application provides a web-based interface for generating graphs, placing robots, assigning tasks, and monitoring the execution of these tasks by the robots.

## Installation and Build

### Prerequisites

- CMake
- A C++ compiler (e.g., GCC)
- Valgrind (optional, for memory checking)
- Google Test (included for unit testing)

### Build Instructions

1. Build the project:
    
    ```bash
    make
    ```
    
2. Run the application:
    
    ```bash
    make run
    ```
    
    The server will start and listen on port 8080. Open your browser and navigate to [http://localhost:8080](http://localhost:8080/) to access the UI.
    
3. (Optional) Run the application with Valgrind for memory checking:
    
    ```bash
    make valgrind
    ```

## Testing

This project includes unit tests using the Google Test framework.

1. Run the tests:
    
    ```bash
    make test
    ```
    
2. (Optional) Run the tests with Valgrind for memory checking:
    
    ```bash
    make test-with-valgrind
    ```

    This will run the tests under Valgrind to check for memory leaks or other memory-related issues.

## Usage

### Web Interface Overview

Once you have opened the UI in your browser, follow these steps:

1. **Generate a Graph:**
    - Enter the number of nodes, waiting areas, charging stations, and pick/drop points.
    - Click `Generate` to create the graph.
    - It is recommended to click `Lock Graph` after generating it to prevent further modifications.
2. **Add Robots:**
    - Use the `Add Robot` button to place robots on the graph.
    - After clicking `Add Robot`, click on the node where you want to place the robot.
    - You can clear all robots at any time using the `Clear Robots` button.
3. **Generate Tasks:**
    - Enter the number of tasks and click `Generate` to create the tasks.
4. **Start Execution:**
    - Once everything is set up, click `Start` to begin task assignment to robots.
    - Robots will execute the tasks in the order they are assigned.
5. **Stop Execution:**
    - Use the `Stop` button to halt all operations. This is crucial, especially when running with Valgrind, as it stops not only the server but also the threads and task/robot processes.


### Future Improvements

- **Robot Status Management:** Implement a comprehensive status system for the robots, including states such as `charging`, `waiting`, `picking`, `dropping`, `moving_to_pick`, and more. This will allow the `robot_manager` to better manage robot actions and transitions between these states.
  
- **Battery Management:** Introduce battery management features where the robot can monitor its battery level, move to a charging station when necessary, and resume tasks once charged. The `robot_manager` should handle putting robots into a waiting state if charging stations are occupied or if the robot's battery is critically low.

- **Collision Avoidance and Navigation:** Improve the robot's navigation logic to manage access to nodes more effectively and avoid collisions. This will involve coordinating robot movements to ensure that only one robot can occupy a node at a time, thereby preventing potential collisions.

- **Enhanced Robot Methods:** Add new methods to the robot class such as `charge`, `wait`, `pick`, `drop`, and `set_status`. Like the `move` method, these should be invoked by the `robot_manager` and added to the robot's execution queue. These methods will enhance the robot's ability to manage its own tasks and respond to dynamic conditions in the environment.

- **Task Assignment Logic:** Refine the task assignment logic within the `robot_manager` to more tightly control how tasks are allocated to robots. This may involve prioritizing tasks based on robot status, battery levels, or proximity to task locations, ensuring that tasks are distributed in a way that optimizes overall efficiency and avoids overloading individual robots.

