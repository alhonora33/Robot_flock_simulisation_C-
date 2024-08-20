/**
 * Fetches the graph data from the server.
 * @returns {Promise<Object>} The graph data in JSON format.
 * @throws Will throw an error if the request fails.
 */
async function fetchGraphData() {
    const response = await fetch('/graph', {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    });

    if (!response.ok) {
        throw new Error('Failed to fetch graph data');
    }

    const data = await response.json(); // Await for the JSON parsing
    return data;
}

/**
 * Generates a random graph by sending a request to the server.
 * @param {number} numNodes - The number of nodes to generate.
 * @param {number} numWaiting - The number of waiting nodes.
 * @param {number} numCharging - The number of charging nodes.
 * @param {number} numPickDrop - The number of pick-drop nodes.
 * @throws Will throw an error if the request fails.
 */
async function fetchGenGraph(numNodes, numWaiting, numCharging, numPickDrop) {
    const params = new URLSearchParams({
        num_node: numNodes,
        num_waiting: numWaiting,
        num_charging: numCharging,
        num_pickdrop: numPickDrop
    });

    const response = await fetch('/gen_graph', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: params.toString()
    });

    if (!response.ok) {
        throw new Error('Failed to fetch graph data');
    }
}

/**
 * Fetches the robot data from the server.
 * @returns {Promise<Object>} The robot data in JSON format.
 * @throws Will throw an error if the request fails.
 */
async function fetchRobotsData() {
    const response = await fetch('/robots', {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    });

    if (!response.ok) {
        throw new Error('Failed to fetch robot data');
    }

    const data = await response.json(); // Await for the JSON parsing
    return data;
}

/**
 * Adds a robot to the system by sending a request to the server.
 * @param {number} x - The x-coordinate where the robot should be placed.
 * @param {number} y - The y-coordinate where the robot should be placed.
 * @throws Will throw an error if the request fails.
 */
async function fetchAddRobot(x, y) {
    const params = new URLSearchParams({
        x: x,
        y: y
    });

    const response = await fetch('/add_robot', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: params.toString()
    });
    if (!response.ok) {
        throw new Error('Failed to add robot');
    }
}

/**
 * Removes all robots from the system by sending a request to the server.
 * @throws Will throw an error if the request fails.
 */
async function fetchRemoveRobots() {
    const response = await fetch('/remove_robots', {
        method: 'POST'
    });

    if (!response.ok) {
        throw new Error('Failed to remove robots');
    }
}

/**
 * Generates random tasks by sending a request to the server.
 * @param {number} numTasks - The number of tasks to generate.
 * @throws Will throw an error if the request fails.
 */
async function fetchGenTasks(numTasks) {
    const params = new URLSearchParams({
        num_tasks: numTasks
    });
    const response = await fetch('/generate_tasks', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: params.toString()
    });

    if (!response.ok) {
        throw new Error('Failed to generate tasks');
    }
}

/**
 * Fetches the task data from the server.
 * @returns {Promise<Object>} The task data in JSON format.
 * @throws Will throw an error if the request fails.
 */
async function fetchGetTasks() {
    const response = await fetch('/tasks', {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    });

    if (!response.ok) {
        throw new Error('Failed to fetch tasks');
    }

    const data = await response.json();
    return data;
}

/**
 * Starts the execution of tasks by sending a request to the server.
 * @throws Will throw an error if the request fails.
 */
async function fetchStart() {
    const response = await fetch('/start', {
        method: 'POST',
    });

    if (!response.ok) {
        throw new Error('Failed to start');
    }

    const message = await response.text();
    alert(message);
}

/**
 * Stops the server by sending a request to the server and displays a message.
 * @throws Will throw an error if the request fails.
 */
async function fetchStopServer() {
    try {
        const response = await fetch('/stop', {
            method: 'POST'
        });

        const message = await response.text();
        alert(message);
    } catch (error) {
        console.error('Error stopping server:', error);
    }
}
