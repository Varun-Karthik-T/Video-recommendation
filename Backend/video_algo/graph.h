#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
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

    vector<Video> aStar(int startId, const vector<string> &targetGenres, int numResults)
    {
        using QueueElement = pair<float, int>; 
        priority_queue<QueueElement, vector<QueueElement>, greater<QueueElement>> pq;
        unordered_map<int, int> cost;
        unordered_map<int, float> heuristic;
        unordered_map<int, int> cameFrom;
        vector<Video> foundVideos;

        pq.push({0, startId});
        cost[startId] = 0;

        unordered_set<int> visited;

        while (!pq.empty() && foundVideos.size() < numResults)
        {
            QueueElement currentElement = pq.top();
            pq.pop();
            int currentId = currentElement.second;

            if (visited.find(currentId) != visited.end())
            {
                continue;
            }
            visited.insert(currentId);

            if (currentId != startId && estimateHeuristic(currentId, targetGenres) > 0.5f)
            {
                foundVideos.push_back(videos[currentId]);
            }

            for (const auto &neighbor : adjList[currentId])
            {
                int neighborId = neighbor.first;
                int weight = neighbor.second;
                int newCost = cost[currentId] + weight;
                if (cost.find(neighborId) == cost.end() || newCost < cost[neighborId])
                {
                    cost[neighborId] = newCost;
                    float heuristicValue = 1.0f - estimateHeuristic(neighborId, targetGenres); // Inverted heuristic
                    pq.push({newCost + heuristicValue, neighborId});
                    cameFrom[neighborId] = currentId;
                }
            }
        }
        return reconstructPath(startId, foundVideos, cameFrom);
    }

    vector<Video> getRelatedVideos(int id, const vector<string> &targetGenres, int numResults)
    {
        for (const auto &genre : targetGenres)
        {
            cout << genre << endl;
        }
        return aStar(id, targetGenres, numResults);
    }

    void loadVertices(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                int id;
                string name, description, video_link, thumbnail_link, genres;
                getline(ss, line, ',');
                id = stoi(line);
                getline(ss, name, ',');
                getline(ss, description, ',');
                getline(ss, video_link, ',');
                getline(ss, thumbnail_link, ',');
                getline(ss, genres, ',');
                Video video(id, name, description, video_link, thumbnail_link, genres);
                addVideo(video);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void loadEdges(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                int from, to, weight;
                char comma;
                ss >> from >> comma >> to >> comma >> weight;
                addEdge(from, to, weight);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void printVertices() const
    {
        for (const auto &entry : videos)
        {
            const Video &video = entry.second;
            cout << "ID: " << video.id << ", Name: " << video.name
                 << ", Description: " << video.description
                 << ", Video Link: " << video.video_link
                 << ", Thumbnail Link: " << video.thumbnail_link
                 << ", Genres: " << video.genres << endl;
        }
    }

    void printAdjacencyList() const
    {
        for (const auto &entry : adjList)
        {
            cout << "Video ID " << entry.first << " is connected to:" << endl;
            for (const auto &neighbor : entry.second)
            {
                cout << "    Video ID " << neighbor.first << " with weight " << neighbor.second << endl;
            }
        }
    }

private:
    unordered_map<int, vector<pair<int, int>>> adjList;
    unordered_map<int, Video> videos;

    float estimateHeuristic(int id, const vector<string> &targetGenres)
    {
        int matchCount = 0;
        for (const auto &genre : targetGenres)
        {
            if (videos[id].genres.find(genre) != string::npos)
            {
                matchCount++;
            }
        }
        return static_cast<float>(matchCount) / targetGenres.size();
    }

    vector<Video> reconstructPath(int startId, const vector<Video> &foundVideos, unordered_map<int, int> &cameFrom)
    {
        vector<Video> path;
        bool firstPath = true;

        for (const auto &video : foundVideos)
        {
            if (!firstPath)
            {
                path.push_back(Video(-1, "----------", "----------", "----------", "----------", "----------"));
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