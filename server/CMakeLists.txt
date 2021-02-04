cmake_minimum_required(VERSION 3.10)
project(server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -g -Wall -o")
add_executable(server server.cpp)