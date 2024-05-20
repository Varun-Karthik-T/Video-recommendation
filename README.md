# Video Recommendation System

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

## Summary

- Install `cmake` and `libboost-all-dev`
- Clone the required repositories
- Build and run the video algorithm server

