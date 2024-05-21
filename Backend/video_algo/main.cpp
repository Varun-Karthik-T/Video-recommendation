#include "crow.h"
#include "splay.h"
#include <sstream>

int main()
{
    crow::SimpleApp app;
    SplayTree splayTree;

    CROW_ROUTE(app, "/api/v1/")
    ([]()
     { return "Hello, Crow!"; });

    CROW_ROUTE(app, "/api/v1/video")
        .methods("POST"_method)([&splayTree](const crow::request &req)
                                {
        auto x = crow::json::load(req.body);
        if (!x)
        {
            return crow::response(400);
        }

        int id = x["id"].i();
        string name = x["name"].s();
        string link = x["link"].s();
        string genre = x["genre"].s();
        int weightage = x["weightage"].i();

        Video video(id, name, link, genre, weightage);
        splayTree.insert(video);

        return crow::response(200); });

    CROW_ROUTE(app, "/api/v1/video/<int>")
    ([&splayTree](int id)
     {
        Video* video = splayTree.find(id);
        if (video)
        {
            crow::json::wvalue jsonResp;
            jsonResp["id"] = video->id;
            jsonResp["name"] = video->name; 
            jsonResp["link"] = video->link;
            jsonResp["genre"] = video->genre;
            jsonResp["weightage"] = video->weightage;

            return crow::response(jsonResp);
        }
        return crow::response(404); });

    app.port(18080).multithreaded().run();

    return 0;
}
