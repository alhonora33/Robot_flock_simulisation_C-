#ifndef SERVER_HPP
#define SERVER_HPP

#include "httplib.hpp"
#include "randomgraph.hpp"
#include "robotsmanager.hpp"
#include "tasksmanager.hpp"
#include <memory>
namespace web
{
    class Server
    {
    public:
        Server() = delete;
        Server(int port, std::shared_ptr<graph::RandomGraph> graph, std::shared_ptr<robot::RobotsManager> robots_manager, std::shared_ptr<task::TasksManager> tasks_manager) noexcept;

        void start();
        void stop();

    private:
        void setHTTPServer();
        void listen();

        const int _port;
        const std::shared_ptr<graph::RandomGraph> _graph;
        const std::shared_ptr<robot::RobotsManager> _robots_manager;
        const std::shared_ptr<task::TasksManager> _tasks_manager;
        httplib::Server _svr;
    };
} // namespace web
#endif // SERVER_HPP
