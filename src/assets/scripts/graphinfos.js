/**
 * Updates the displayed information about the graph, such as the total number of nodes,
 * and the count of nodes in each category (waiting, charging, pick-drop).
 * @param {Object} graphData - The data representing the graph, including nodes and their properties.
 */
function updateGraphInfos(graphData) {
    // Update the total number of nodes displayed
    document.getElementById('num_nodes').textContent = graphData.nodes.length;

    // Update the count of 'waiting' nodes displayed
    document.getElementById('num_wait').textContent = graphData.nodes.filter(node => node.p === 'waiting').length;

    // Update the count of 'charging' nodes displayed
    document.getElementById('num_charg').textContent = graphData.nodes.filter(node => node.p === 'charging').length;

    // Update the count of 'pick-drop' nodes displayed
    document.getElementById('num_pick_drop').textContent = graphData.nodes.filter(node => node.p === 'pickdrop').length;
}