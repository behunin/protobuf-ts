cmake_minimum_required(VERSION 3.10)

project(protobuf-ts LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)

find_library(libprotobuf protobuf REQUIRED)
find_library(libprotoc protoc REQUIRED)

add_executable(protobuf-ts protobuf-ts.cpp)

target_link_libraries(protobuf-ts protoc protobuf)