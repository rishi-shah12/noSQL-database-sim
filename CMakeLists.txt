cmake_minimum_required(VERSION 3.17)
project(jsonOutput)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/Cellar/jsoncpp/1.9.4_1/include/json/")

add_executable(jsonOutput main.cpp)