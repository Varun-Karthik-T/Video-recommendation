#include "crow.h"
#include "splay.h"
#include "graph.h"
#include <sstream>
#include <unordered_set>

class CORSHandler
{
public:
    struct context
    {
    };

    void before_handle(crow::request &req, crow::response &res, context &)
    {
        res.add_header("Access-Control-Allow-Origin", "*"); 
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

        if (req.method == "OPTIONS"_method)
        {
            res.code = 204;
            res.end();
        }
    }

    void after_handle(crow::request &req, crow::response &res, context &)
    {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }
};

vector<string> splitGenres(const string &genres)
{
    vector<string> result;
    stringstream ss(genres);
    string genre;
    while (getline(ss, genre, ' '))
    { // assuming genres are space-separated
        result.push_back(genre);
    }
    return result;
}

int main()
{
    crow::App<CORSHandler> app;

    SplayTree splayTree;
    Graph graph;
    graph.loadVertices("videos.txt");
    graph.loadEdges("edges.txt");

    cout << "Vertices in the graph:" << endl;
    graph.printVertices();

    cout << "\nAdjacency List:" << endl;
    graph.printAdjacencyList();

    CROW_ROUTE(app, "/api/v1/")
    ([]()
     { return "Hello, Crow!"; });

    CROW_ROUTE(app, "/api/v1/video")
        .methods("POST"_method)([&splayTree](const crow::request &req)
                                {
        auto json = crow::json::load(req.body);
        if (!json)
        {
            return crow::response(400, "Invalid JSON");
        }

        if (!json.has("id") || !json.has("name") || !json.has("video_link") || !json.has("genres") || !json.has("thumbnail_link") || !json.has("description"))
        {
            return crow::response(400, "Missing required fields");
        }

        int id = json["id"].i();
        std::string name = json["name"].s();
        std::string video_link = json["video_link"].s();
        std::string genres = json["genres"].s();
        std::string thumbnail_link=json["thumbnail_link"].s();
        std::string description=json["description"].s();
        Video video(id, name, description, video_link,thumbnail_link , genres);
        splayTree.insert(video);
        splayTree.printTree();

        return crow::response(200); });

    CROW_ROUTE(app, "/api/v1/video/suggestion")
        .methods("GET"_method)([&splayTree, &graph](const crow::request &req)
                               {

                            cout<<".....Fetching Video Content....\n";
        if (splayTree.isEmpty())
        {
            vector<Video> allVideos = graph.getAllVideos();
            cout<<"Suggested videos are:\n";
        for (int i = 0; i < allVideos.size(); ++i)
        {
            
            cout<<allVideos[i].id<<" ";
        }
        cout<<endl;
            

            crow::json::wvalue jsonResp;
            jsonResp["videos"] = crow::json::wvalue::list();
            for (size_t i = 0; i < allVideos.size(); ++i)
            {
                const auto &video = allVideos[i];
                jsonResp["videos"][i] = crow::json::wvalue{
                    {"id", video.id},
                    {"name", video.name},
                    {"description", video.description},
                    {"video_link", video.video_link},
                    {"thumbnail_link", video.thumbnail_link},
                    {"genres", video.genres}
                };
            }
            return crow::response(jsonResp);
        }

        vector<Video> splayVideos = splayTree.traverse();
    

        
        unordered_set<int> uniqueIds;

        for (const auto &video : splayVideos)
        {
            uniqueIds.insert(video.id);
        }

    
        vector<Video> suggestedVideos;

        for (const auto &video : splayVideos)
        {
            vector<string> targetgenres = splitGenres(video.genres);
            vector<Video> relatedVideos = graph.getRelatedVideos(video.id, targetgenres, 4);
          
          
            for (const auto &relatedVideo : relatedVideos)
            {
                if (uniqueIds.find(relatedVideo.id) == uniqueIds.end())
                {
                    suggestedVideos.push_back(relatedVideo);
                }
            }
        }
        
        // if (suggestedVideos.size() < 15)
        // {
        //     vector<Video> allVideos = graph.getAllVideos();
        //     for (const auto &video : allVideos)
        //     {
        //         if (uniqueIds.find(video.id) == uniqueIds.end())
        //         {   
        //             suggestedVideos.push_back(video);
        //             uniqueIds.insert(video.id); 
        //             if (suggestedVideos.size() >= 15) {
        //                 break;
        //             }
        //         }
        //     }
        // }
        cout<<"Suggested videos are:\n";
        for (int i = 0; i < suggestedVideos.size(); ++i)
        {
            
            cout<<suggestedVideos[i].id<<" ";
        }
        cout<<endl;
        
        
        crow::json::wvalue jsonResp;
        jsonResp["videos"] = crow::json::wvalue::list();
        if(suggestedVideos.size()){}
        for (size_t i = 0; i < suggestedVideos.size(); ++i)
        {
            //cout<<suggestedVideos[i].id<<" ";
            const auto &video = suggestedVideos[i];
            jsonResp["videos"][i] = crow::json::wvalue{
                {"id", video.id},
                {"name", video.name},
                {"description", video.description},
                {"video_link", video.video_link},
                {"thumbnail_link", video.thumbnail_link},
                {"genres", video.genres}
            };
        }
        return crow::response(jsonResp); });

    app.port(18080).multithreaded().run();

    return 0;
}