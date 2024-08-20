#include "server.hpp"

namespace web
{

  Server::Server(int port, std::shared_ptr<graph::RandomGraph> graph, std::shared_ptr<robot::RobotsManager> robots_manager, std::shared_ptr<task::TasksManager> tasks_manager) noexcept
      : _port(port), _graph(graph), _robots_manager(robots_manager), _tasks_manager(tasks_manager)
  {
    setHTTPServer();
  }

  void Server::start() { listen(); }

  void Server::stop() { _svr.stop(); }

  void Server::setHTTPServer()
  {
    _svr.set_mount_point("/", "./assets");

    _svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
             {
    (void)req;
    std::ifstream t("./assets/index.html");
    if (t) {
      std::string page((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
      res.set_content(page, "text/html");
      res.status = 200;
    } else {
      res.status = 404;
      res.set_content("404 - File not found", "text/plain");
    } });

    _svr.Post("/stop", [&](const httplib::Request &req, httplib::Response &res)
              {
    (void)req;
    stop();
    _robots_manager->clear();
    res.status = 200;
    res.set_content("Server stopped", "text/plain"); });

    _svr.Post("/gen_graph", [&](const httplib::Request &req, httplib::Response &res)
              {
    try {
        auto num_node = std::stoi(req.get_param_value("num_node"));
        auto num_waiting = std::stoi(req.get_param_value("num_waiting"));
        auto num_charging = std::stoi(req.get_param_value("num_charging"));
        auto num_pickdrop = std::stoi(req.get_param_value("num_pickdrop"));

        _graph->genRandomGraph(num_node, num_waiting, num_charging, num_pickdrop);
        res.status = 200;
    } catch (const std::exception &e) {
        res.status = 400;
        res.set_content("Invalid parameters", "text/plain");
    } });

    _svr.Post("/add_robot", [&](const httplib::Request &req, httplib::Response &res)
              {
    try {
        auto x = std::stof(req.get_param_value("x"));
        auto y = std::stof(req.get_param_value("y"));
        _robots_manager->addRobot(x, y);
        res.status = 200;
    } catch (const std::exception &e) {
        res.status = 400;
        res.set_content("Invalid parameters", "text/plain");
    } });

    _svr.Post("/remove_robots", [&](const httplib::Request &req, httplib::Response &res)
              {
    try {
        (void)req;
        _robots_manager->clear();
        res.status = 200;
    } catch (const std::exception &e) {
        res.status = 400;
        res.set_content("Invalid parameters", "text/plain");
    } });

    _svr.Post("/generate_tasks", [&](const httplib::Request &req, httplib::Response &res)
              {
    try {
        auto num_tasks = std::stoi(req.get_param_value("num_tasks"));
        _tasks_manager->addRandomTasks(num_tasks);
        res.status = 200;
    } catch (const std::exception &e) {
        res.status = 400;
        res.set_content("Invalid parameters", "text/plain");
    } });

    _svr.Get("/tasks", [&](const httplib::Request &req, httplib::Response &res)
             {
    (void)req;
    std::string tasks_json = _tasks_manager->getToJson();
    res.set_content(tasks_json, "application/json");
    res.status = 200; });
  
    _svr.Get("/graph", [&](const httplib::Request &req, httplib::Response &res)
             {
    (void)req;
    std::string graph_json = _graph->getToJson();
    res.set_content(graph_json, "application/json");
    res.status = 200; });

    _svr.Get("/robots", [&](const httplib::Request &req, httplib::Response &res)
             {
    (void)req;
    std::string robots_json = _robots_manager->getToJson();
    res.set_content(robots_json, "application/json");
    res.status = 200; });

    _svr.Post("/start", [&](const httplib::Request &, httplib::Response &res) {
        _robots_manager->assignAndExecuteTasks();
        res.set_content("started successfully!", "text/plain");
    });

    _svr.set_error_handler([](const httplib::Request &req, httplib::Response &res)
                           {
          (void)req;
          res.status = 404;
          res.set_content("404 - Not Found", "text/plain"); });

    //_svr.set_logger([](const httplib::Request &req, const httplib::Response &res)
    //                { std::cout << req.method << " " << req.path << " " << res.status << std::endl; });

    _svr.set_post_routing_handler([](const httplib::Request &req, httplib::Response &res)
                                  {
          if (res.status == 404)
          {
            std::vector<std::string> supported_methods = {
                "GET", "POST"};
            if (std::find(supported_methods.begin(), supported_methods.end(),
                          req.method) == supported_methods.end())
            {
              res.set_content("405 - Method Not Allowed", "text/plain");
              res.status = 405;
            }
          } });
  }

  void Server::listen()
  {
    std::cout << "Server is listening on port " << _port << std::endl;
    std::cout << "Open your browser and navigate to http://localhost:" << _port
              << std::endl;
    _svr.listen("0.0.0.0", _port);
  }

} // namespace web