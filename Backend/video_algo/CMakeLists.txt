cmake_minimum_required(VERSION 3.10)

project(video_algo)

set(CMAKE_CXX_STANDARD 11)

# Include Crow headers
include_directories(../Crow/include)

# Include Asio headers
include_directories(../asio/asio/include)

# Add your source files here
add_executable(video_algo main.cpp)

# Link Boost libraries if necessary
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(video_algo ${Boost_LIBRARIES})
endif()
