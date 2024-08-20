/**
 * Event listener for the "Generate Graph" button.
 * Retrieves the input values for the number of nodes, waiting nodes, charging nodes, and pick-drop nodes.
 * Validates the input values to ensure they are at least 1.
 * If valid, clears the existing graph, removes robots, generates a new graph, and redraws the graph.
 * If invalid, displays an alert message to the user.
 */
document.getElementById('generate_button').addEventListener('click', async function () {
    const numNode = parseInt(document.getElementById('num_node').value);
    const numWaiting = parseInt(document.getElementById('num_waiting').value);
    const numCharging = parseInt(document.getElementById('num_charging').value);
    const numPickDrop = parseInt(document.getElementById('num_pickdrop').value);

    if (numNode >= 1 && numWaiting >= 1 && numCharging >= 1 && numPickDrop >= 1) {
        clearGraph();
        await fetchRemoveRobots();
        await fetchGenGraph(numNode, numWaiting, numCharging, numPickDrop);
        drawGraph();
    } else {
        alert('Please enter at least 1 node for each field.');
    }
});

/**
 * Event listener for the "Lock/Unlock Graph" button.
 * Toggles the visibility of the graph generation form and the generate button.
 * Changes the text content of the lock button based on the current state (lock/unlock).
 */
document.getElementById('lock_button').addEventListener('click', function () {
    const form = document.getElementById('graph_form');
    const generateButton = document.getElementById('generate_button');
    const lockButton = document.getElementById('lock_button');

    if (lockButton.textContent === 'Lock Graph') {
        form.classList.add('hidden');
        generateButton.classList.add('hidden');
        lockButton.textContent = 'Unlock Graph';
    } else {
        form.classList.remove('hidden');
        generateButton.classList.remove('hidden');
        lockButton.textContent = 'Lock Graph';
    }
});
