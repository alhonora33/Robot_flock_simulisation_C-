/**
 * Event listener for the "Add Robot" button.
 * Allows the user to select a node on the graph where a robot will be placed.
 * Once a node is selected, sends a request to add the robot at the selected node's position.
 * Disables node selection after the robot is placed.
 */
document.getElementById('add_robot_button').addEventListener('click', () => {
    const cy = window.cy; // Assuming cy instance is globally accessible or passed
    if (!cy) return;

    // Set nodes selectable
    cy.nodes().selectify();

    // Event listener for node selection
    cy.once('select', 'node', async function(evt) {
        const node = evt.target;
        const position = node.position();
        
        // Add robot at the selected node's position
        await fetchAddRobot(position.x, position.y);

        // Deselect and disable further selection
        cy.nodes().unselectify();
    });

    alert('Please select a node to place the robot');
});

/**
 * Event listener for the "Clear Robots" button.
 * Clears all robots from the graph visualization.
 * Sends a request to remove all robots from the system.
 */
document.getElementById('clear_robots_button').addEventListener('click', async () => {
    clearRobots();
    await fetchRemoveRobots();
});
