# Video Recommendation System - Astar

This project aims to manage and explore a collection of videos using graph and splay tree data structures. Videos are represented by a `Video` struct, which includes attributes such as ID, name, description, video link, thumbnail link, and genres. The `Graph` class allows for the addition of videos and edges between them, representing relationships or similarities. It provides functionality to load vertices and edges from files, print the list of videos (vertices) and their connections (adjacency list), and perform an A* search to find videos of a specified genre. Additionally, a splay tree is used for efficient video insertion and retrieval, ensuring that recently accessed videos are quicker to access. This combination of data structures supports efficient organization and retrieval of video data, making it suitable for applications like video recommendation systems.

## Backend Setup

Follow the steps below to set up the backend for the video recommendation system.

### Prerequisites

Ensure you have `cmake` and `libboost-all-dev` installed on your system. You can install them using the following command:

```sh
sudo apt install cmake libboost-all-dev
```

### Cloning Repositories

Clone the necessary repositories into your backend directory:

```sh
git clone https://github.com/CrowCpp/Crow.git
git clone https://github.com/chriskohlhoff/asio.git
```

### Building the Video Algorithm

Navigate to the `video_algo` directory, create a build directory, and compile the code:

```sh
cd video_algo
mkdir build
cd build
cmake ..
make
./video_algo
```

This will start the server.

## Frontend Setup

Navigate to the `Frontend` directory, install the dependencies, and start the development server:

```sh
cd Frontend
npm install
npm run dev
```

## Summary

- Install `cmake` and `libboost-all-dev`
- Clone the required repositories
- Build and run the video algorithm server
- Set up and run the frontend development server

Following these steps will ensure that both the backend and frontend of the video recommendation system are properly set up and running.
