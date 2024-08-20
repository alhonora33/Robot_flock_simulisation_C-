/**
 * Event listener for the "Stop" button.
 * Disables the stop button to prevent multiple clicks.
 * Clears the current graph visualization.
 * Sends a request to stop the server and performs the associated cleanup.
 */
document.getElementById('stop_button').addEventListener('click', async () => {
    stop_button.disabled = true;
    clearGraph();
    await fetchStopServer();
});

/**
 * Event listener for the "Start" button.
 * Attempts to start the server and handles any errors that occur during the process.
 * Logs an error to the console if the start process fails.
 */
document.getElementById('start_button').addEventListener('click', async () => {
    try {
        await fetchStart();
    } catch (error) {
        console.error('Error starting:', error);
    }
});
