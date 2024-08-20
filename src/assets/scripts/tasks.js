/**
 * Fetches the list of tasks from the server and updates the tasks table in the UI.
 * Clears the current task list and repopulates it with the latest data.
 * Applies status-based color classes to each task row for visual distinction.
 */
async function loadTasks() {
    try {
        const response = await fetchGetTasks();
        const tasks = response.tasks;

        const tasksBody = document.getElementById('tasks_body');
        tasksBody.innerHTML = '';

        tasks.forEach(task => {
            const row = document.createElement('tr');
            row.classList.add('task-row');

            // Apply status-based color class
            if (task.status === 'Done') {
                row.classList.add('task-done');
            } else if (task.status === 'Pending') {
                row.classList.add('task-pending');
            } else if (task.status === 'InProgress') {
                row.classList.add('task-inprogress');
            }

            row.innerHTML = `
                <td>${task.id}</td>
                <td>${task.node_id_pick}</td>
                <td>${task.node_id_drop}</td>
                <td>${task.status}</td>
                <td>${task.assigned_robot_id}</td>
            `;

            tasksBody.appendChild(row);
        });
    } catch (error) {
        console.error('Error loading tasks:', error);
    }
}

/**
 * Sets an interval to refresh the tasks list every 1000 milliseconds (1 second).
 */
setInterval(loadTasks, 1000);
