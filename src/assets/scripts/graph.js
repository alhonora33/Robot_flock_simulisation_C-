/**
 * Styles configuration for Cytoscape elements such as nodes and edges.
 */
let interval = null;

const cytoscapeStyles = [
    {
        selector: 'node',
        style: {
            'background-color': 'data(backgroundColor)',
            'label': 'data(id)',
            'width': 20,
            'height': 20,
            'text-valign': 'center',
            'text-halign': 'center',
            'color': '#fff',
            'font-size': 8,
            'text-outline-width': 1,
            'text-outline-color': '#555',
        }
    },
    {
        selector: 'edge',
        style: {
            'width': 2,
            'line-color': '#ccc',
            'target-arrow-color': '#ccc',
            'target-arrow-shape': 'none',
            'curve-style': 'straight'
        }
    },
    {
        selector: '.robot',
        style: {
            'background-color': '#FFFF00',
            'width': 25,
            'height': 25,
            'shape': 'round-rectangle',
            'border-width': 1,
            'border-color': '#710d76',
            'opacity': 0.6,
            'label': ''
        }
    },
    {
        selector: '.robot-directional',
        style: {
            'background-color': '#710d76',
            'width': 15,
            'height': 15,
            'shape': 'ellipse',
            'label': 'data(label)',
            'color': '#fff',
            'font-size': 8,
            'text-valign': 'center',
            'text-halign': 'center'
        }
    }
];

/**
 * Initializes and creates the Cytoscape graph visualization with the provided graph data.
 * @param {Object} graphData - The data representing nodes and edges of the graph.
 */
function createGraph(graphData) {
    const cy = cytoscape({
        container: document.getElementById('graph'),
        elements: [],
        style: cytoscapeStyles,
        layout: { name: 'preset' }
    });

    window.cy = cy;
    addGraphElements(graphData);
    startRobotUpdate();
}

/**
 * Adds nodes and edges to the Cytoscape graph based on the provided graph data.
 * @param {Object} graphData - The data representing nodes and edges of the graph.
 */
function addGraphElements(graphData) {
    graphData.nodes.forEach(node => {
        addGraphNode(node);
    });
    graphData.edges.forEach(edge => {
        addGraphEdge(edge);
    });

    cy.layout({ name: 'preset' }).run();
}

/**
 * Adds a single node to the Cytoscape graph.
 * @param {Object} node - The node data including id, position, and property.
 */
function addGraphNode(node) {
    cy.add({
        group: 'nodes',
        data: {
            id: node.id,
            property: node.p,
            backgroundColor: getBackgroundColor(node.p)
        },
        position: { x: node.x, y: node.y },
        locked: true, // Static nodes should be locked
        grabbable: false
    });
}

/**
 * Adds a single edge to the Cytoscape graph.
 * @param {Object} edge - The edge data including source and target node IDs.
 */
function addGraphEdge(edge) {
    cy.add({
        group: 'edges',
        data: { id: `${edge.n1}-${edge.n2}`, source: edge.n1, target: edge.n2 },
        locked: true, // Edges remain static
        grabbable: false
    });
}

/**
 * Determines the background color of a node based on its property.
 * @param {string} property - The property of the node (e.g., 'charging', 'pickdrop').
 * @returns {string} The background color corresponding to the node's property.
 */
function getBackgroundColor(property) {
    const colorMap = {
        'charging': 'green',
        'pickdrop': 'blue',
        'waiting': 'yellow'
    };
    return colorMap[property] || 'red';
}

/**
 * Periodically updates the positions and states of the robots on the graph.
 */
async function updateRobots() {
    try {
        const robotsData = await fetchRobotsData();
        console.log('Robots:', robotsData);

        robotsData.robots.forEach(robot => {
            const robotId = `robot-${robot.id}`;
            const robotNode = cy.getElementById(robotId);

            if (robotNode.length > 0) {
                updateRobotNode(robotNode, robot);
            } else {
                addRobotNode(robot, robotId);
            }

            updateRobotMarker(robot);
        });
    } catch (error) {
        console.error('Failed to update robots:', error);
    }
}

/**
 * Updates the position of an existing robot node on the graph.
 * @param {Object} robotNode - The Cytoscape node object representing the robot.
 * @param {Object} robot - The data of the robot including new position.
 */
function updateRobotNode(robotNode, robot) {
    // Update the robot's position based on the received data
    robotNode.position({ x: robot.x, y: robot.y });
}

/**
 * Adds a new robot node to the graph.
 * @param {Object} robot - The data of the robot including position.
 * @param {string} robotId - The ID for the new robot node.
 */
function addRobotNode(robot, robotId) {
    cy.add({
        group: 'nodes',
        data: {
            id: robotId,
            class: 'robot'  // Using class for style
        },
        position: { x: robot.x, y: robot.y },
        classes: 'robot',
        locked: false,  // Robot nodes must be unlocked to allow movement
        grabbable: false // Prevent manual dragging or selection
    });
}

/**
 * Updates or adds a directional marker for the robot based on its movement and angle.
 * @param {Object} robot - The data of the robot including position and angle.
 */
function updateRobotMarker(robot) {
    const markerId = `robot-marker-${robot.id}`;
    const markerNode = cy.getElementById(markerId);
    const offset = getOffset(robot.angle);

    if (markerNode.length > 0) {
        // Update the position of the directional marker based on robot movement
        markerNode.position({ x: robot.x + offset.x, y: robot.y + offset.y });
        markerNode.data('label', `${robot.id}`);
    } else {
        addRobotMarker(robot, markerId, offset);
    }
}

/**
 * Calculates the offset for a directional marker based on the robot's angle.
 * @param {number} angle - The angle of the robot in degrees.
 * @returns {Object} The x and y offset for the directional marker.
 */
function getOffset(angle) {
    const radian = angle * Math.PI / 180;
    return {
        x: 15 * Math.cos(radian),
        y: 15 * Math.sin(radian)
    };
}

/**
 * Adds a directional marker node for a robot on the graph.
 * @param {Object} robot - The data of the robot including position and angle.
 * @param {string} markerId - The ID for the new marker node.
 * @param {Object} offset - The x and y offset for the marker node's position.
 */
function addRobotMarker(robot, markerId, offset) {
    cy.add({
        group: 'nodes',
        data: {
            id: markerId,
            label: `${robot.id}`,
            class: 'robot-directional'
        },
        position: { x: robot.x + offset.x, y: robot.y + offset.y },
        classes: 'robot-directional',
        locked: false,  // Directional marker must also be unlocked for movement
        grabbable: false // Prevent manual dragging or selection
    });
}

/**
 * Starts the periodic update of robot positions on the graph.
 */
function startRobotUpdate() {
    interval = setInterval(updateRobots, 50);
}

/**
 * Fetches the graph data and initializes the graph visualization.
 */
async function drawGraph() {
    try {
        const graphData = await fetchGraphData();
        createGraph(graphData);
        updateGraphInfos(graphData);
    } catch (error) {
        console.error('Failed to draw graph:', error);
    }
}

/**
 * Clears all robot nodes and markers from the graph.
 */
function clearRobots() {
    cy.remove(cy.elements('.robot, .robot-directional'));
}

/**
 * Clears the entire graph visualization and stops the robot update interval.
 */
function clearGraph() {
    document.getElementById('graph').innerHTML = '';
    if (interval) {
        clearInterval(interval);
        interval = null;
    }
}
