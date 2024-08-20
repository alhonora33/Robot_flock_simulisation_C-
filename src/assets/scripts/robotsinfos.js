/**
 * Periodically fetches the robot data and updates the robot details displayed on the UI.
 * If a robot's details are already displayed, updates the existing element.
 * If a robot's details are not yet displayed, creates a new element to display the robot's information.
 */
async function updateRobotDetails() {
    try {
        const robotsData = await fetchRobotsData();

        robotsData.robots.forEach(robot => {
            const robotInfoId = `robot-info-${robot.id}`;
            const robotInfoElement = document.getElementById(robotInfoId);

            if (robotInfoElement) {
                updateRobotInfo(robotInfoElement, robot);
            } else {
                addRobotInfo(robot, robotInfoId);
            }
        });
    } catch (error) {
        console.error('Failed to update robots details:', error);
    }
}

/**
 * Updates the displayed information for a specific robot in the UI.
 * @param {HTMLElement} robotInfoElement - The HTML element where the robot's information is displayed.
 * @param {Object} robot - The robot data including id, battery, x, and y coordinates.
 */
function updateRobotInfo(robotInfoElement, robot) {
    robotInfoElement.innerHTML = `
        <div class="robot-details-line">
            <span>ID: ${robot.id}</span>
            <span>Batterie: ${robot.battery}%</span>
        </div>
        <div class="robot-details-line">
            <span>X: ${robot.x}</span>
            <span>Y: ${robot.y}</span>
        </div>
    `;
}

/**
 * Creates and adds a new HTML element to display a robot's details in the UI.
 * @param {Object} robot - The robot data including id, battery, x, and y coordinates.
 * @param {string} robotInfoId - The unique ID to assign to the HTML element for this robot's information.
 */
function addRobotInfo(robot, robotInfoId) {
    const robotsInfoContainer = document.getElementById('robots_info');

    const robotElement = document.createElement('div');
    robotElement.classList.add('robot-info');
    robotElement.id = robotInfoId;

    robotElement.innerHTML = `
        <div class="robot-details-line">
            <span>ID: ${robot.id}</span>
            <span>Batterie: ${robot.battery}%</span>
        </div>
        <div class="robot-details-line">
            <span>X: ${robot.x}</span>
            <span>Y: ${robot.y}</span>
        </div>
    `;

    robotsInfoContainer.appendChild(robotElement);
}

/**
 * Sets an interval to periodically update the robot details every 2000 milliseconds (2 seconds).
 */
setInterval(updateRobotDetails, 2000);
