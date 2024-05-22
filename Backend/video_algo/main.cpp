#include "crow.h"
#include "splay.h"
// #include "json.hpp"
// #include "graph.h"
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
        // cout << "what is this";
        auto json = crow::json::load(req.body);
        if (!json)
        {
            return crow::response(400, "Invalid JSON");
        }

        if (!json.has("id") || !json.has("name") || !json.has("link") || !json.has("genre"))
        {
            return crow::response(400, "Missing required fields");
        }

        int id = json["id"].i();
        std::string name = json["name"].s();
        std::string link = json["link"].s();
        std::string genre = json["genre"].s();

        Video video(id, name, link, genre);
        splayTree.insert(video);
        splayTree.printTree();

        return crow::response(200); });

    // CROW_ROUTE(app, "/api/v1/video/<int>")
    // ([&splayTree](int id)
    //  {
    //     Video *video = splayTree.find(id);
    //     if (video)
    //     {
    //         crow::json::wvalue jsonResp;
    //         jsonResp["id"] = video->id;
    //         jsonResp["name"] = video->name;
    //         jsonResp["link"] = video->link;
    //         jsonResp["genre"] = video->genre;

    //         return crow::response(jsonResp);
    //     }
    //     return crow::response(404); });

    // CROW_ROUTE(app, "/api/v1/video/suggestion")
    //     .methods("POST"_method)([&splayTree, &graph](const crow::request &req)
    //                             {
    // // Check if the splay tree is empty
    // if (splayTree.isEmpty())
    // {
    //     // If the splay tree is empty, fetch all videos from the graph
    //     vector<Video> allVideos = graph.getAllVideos();
    //     // Convert the vector of videos to a JSON array
    //     crow::json::wvalue jsonResp;
    //     jsonResp["videos"] = crow::json::load(allVideos);
    //     return crow::response(jsonResp);
    // }

    // // If the splay tree is not empty, traverse it to get all videos
    // vector<Video> splayVideos = splayTree.traverse();

    // // Create a set to store unique video IDs
    // unordered_set<int> uniqueIds;

    // // Traverse through the splay tree videos and store their IDs in the set
    // for (const auto &video : splayVideos)
    // {
    //     uniqueIds.insert(video.id);
    // }

    // // Create a vector to store final suggested videos
    // vector<Video> suggestedVideos;

    // // Traverse through the splay tree videos and find related videos for each
    // for (const auto &video : splayVideos)
    // {
    //     // Get related videos from the graph for the current video
    //     vector<Video> relatedVideos = graph.getRelatedVideos(video.id,video.genre,4);

    //     // Traverse through the related videos and add them to the final list if not already watched
    //     for (const auto &relatedVideo : relatedVideos)
    //     {
    //         if (uniqueIds.find(relatedVideo.id) == uniqueIds.end())
    //         {
    //             suggestedVideos.push_back(relatedVideo);
    //         }
    //     }
    // }

    // // Convert the vector of suggested videos to a JSON array
    // crow::json::wvalue jsonResp;
    // jsonResp["videos"] = crow::json::load(suggestedVideos);
    // return crow::response(jsonResp); });

    app.port(18080).multithreaded().run();

    return 0;
}
