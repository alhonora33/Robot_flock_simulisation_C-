#include "randomgraph.hpp"
#include "server.hpp"
#include "robotsmanager.hpp"
#include "tasksmanager.hpp"

#include <future>

int main()
{
    std::shared_ptr<graph::RandomGraph> graph = std::make_shared<graph::RandomGraph>();

    std::shared_ptr<task::TasksManager> tasksManager = std::make_shared<task::TasksManager>(graph);

    std::shared_ptr<robot::RobotsManager> robotsManager = std::make_shared<robot::RobotsManager>(graph, tasksManager);

    web::Server server{8080, graph, robotsManager, tasksManager};

    auto serverFuture = std::async(std::launch::async, [&server]
                                   { server.start(); });

    return 0;
}