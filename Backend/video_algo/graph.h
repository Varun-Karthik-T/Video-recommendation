#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include "splay.h"

using namespace std;

class Graph
{
public:
    void addVideo(const Video &video)
    {
        adjList[video.id] = {};
        videos[video.id] = video;
    }

    void addEdge(int from, int to, int weight)
    {
        adjList[from].push_back({to, weight});
    }

    vector<Video> getAllVideos() const
    {
        vector<Video> allVideos;
        for (const auto &entry : videos)
        {
            allVideos.push_back(entry.second);
        }
        return allVideos;
    }

    vector<Video> aStar(int startId, const string &targetGenre, int numResults)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<int>> pq;
        unordered_map<int, int> cost;
        unordered_map<int, int> heuristic;
        unordered_map<int, int> cameFrom;
        vector<Video> foundVideos;

        pq.push({0, startId});
        cost[startId] = 0;

        unordered_set<int> visited; // Track visited nodes

        while (!pq.empty() && foundVideos.size() < numResults)
        {
            auto [currentCost, currentId] = pq.top();
            pq.pop();

            if (visited.find(currentId) != visited.end()) // Skip if already visited
            {
                continue;
            }
            visited.insert(currentId); // Mark as visited

            if (currentId != startId && videos[currentId].genre == targetGenre)
            {
                foundVideos.push_back(videos[currentId]);
            }

            for (auto [neighborId, weight] : adjList[currentId])
            {
                int newCost = currentCost + weight;
                if (cost.find(neighborId) == cost.end() || newCost < cost[neighborId])
                {
                    cost[neighborId] = newCost;
                    heuristic[neighborId] = newCost + estimateHeuristic(neighborId, targetGenre);
                    pq.push({heuristic[neighborId], neighborId});
                    cameFrom[neighborId] = currentId;
                }
            }
        }
        return reconstructPath(startId, foundVideos, cameFrom);
    }

    pair<vector<Video>, vector<Video>> aStar1(int startId, const string &targetGenre, int numResults)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<int>> pq;
        unordered_map<int, int> cost;
        unordered_map<int, int> heuristic;
        unordered_map<int, int> cameFrom;
        vector<Video> foundVideos;

        pq.push({0, startId});
        cost[startId] = 0;

        unordered_set<int> visited; // Track visited nodes

        while (!pq.empty() && foundVideos.size() < numResults)
        {
            auto [currentCost, currentId] = pq.top();
            pq.pop();

            if (visited.find(currentId) != visited.end()) // Skip if already visited
            {
                continue;
            }
            visited.insert(currentId); // Mark as visited

            if (currentId != startId && videos[currentId].genre == targetGenre)
            {
                foundVideos.push_back(videos[currentId]);
            }

            for (auto [neighborId, weight] : adjList[currentId])
            {
                int newCost = currentCost + weight;
                if (cost.find(neighborId) == cost.end() || newCost < cost[neighborId])
                {
                    cost[neighborId] = newCost;
                    heuristic[neighborId] = newCost + estimateHeuristic(neighborId, targetGenre);
                    pq.push({heuristic[neighborId], neighborId});
                    cameFrom[neighborId] = currentId;
                }
            }
        }
        vector<Video> path = reconstructPath(startId, foundVideos, cameFrom);
        return make_pair(foundVideos, path);
    }

    vector<Video> getRelatedVideos(int id, const string &targetGenre, int numResults)
    {
        auto [foundVideos, _] = aStar1(id, targetGenre, numResults);
        return foundVideos;
    }

private:
    unordered_map<int, vector<pair<int, int>>> adjList;
    unordered_map<int, Video> videos;

    int estimateHeuristic(int id, const string &targetGenre)
    {
        return videos[id].genre == targetGenre ? 0 : 1;
    }

    vector<Video> reconstructPath(int startId, const vector<Video> &foundVideos, unordered_map<int, int> &cameFrom)
    {
        vector<Video> path;
        bool firstPath = true;

        for (const auto &video : foundVideos)
        {
            if (!firstPath)
            {
                // Add a separation between paths
                path.push_back(Video(-1, "----------", "----------", "----------"));
            }
            firstPath = false;

            vector<Video> partialPath;
            for (int id = video.id; id != startId; id = cameFrom[id])
            {
                partialPath.push_back(videos[id]);
            }
            partialPath.push_back(videos[startId]);
            reverse(partialPath.begin(), partialPath.end());
            path.insert(path.end(), partialPath.begin(), partialPath.end());
        }
        return path;
    }
};

#endif // GRAPH_H
