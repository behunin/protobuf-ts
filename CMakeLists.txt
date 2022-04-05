cmake_minimum_required(VERSION 3.10)

project(protobuf-ts)

find_library(libprotobuf protobuf REQUIRED)
find_library(libprotoc protoc REQUIRED)

add_executable(protobuf-ts protobuf-ts.cpp)

target_link_libraries(protobuf-ts protoc protobuf)