/**
 * Event listener for the "Generate Tasks" button.
 * Retrieves the number of tasks to generate from the input field.
 * Validates the input to ensure that at least 1 task is requested.
 * If valid, sends a request to generate the specified number of tasks.
 * If invalid, displays an alert message to the user.
 */
document.getElementById('generate_tasks_button').addEventListener('click', async function() {
    const numTasks = document.getElementById('num_tasks').value;
    if (numTasks >= 1) {
        await fetchGenTasks(numTasks);
    } else {
        alert('Please enter at least 1 task.');
    }
});