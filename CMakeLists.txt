cmake_minimum_required(VERSION 3.15)

# Basic setup

project(
    Raft 
    VERSION 0.1
    DESCRIPTION "Raft implementation in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# fetch library URLs
include(FetchContent)
set(JSON_LIB https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
set(JSON_LIB_LINK nlohmann_json::nlohmann_json)
set(PLOG_LIB https://github.com/SergiusTheBest/plog/archive/refs/tags/1.1.10.tar.gz)

# (TODO: kyuds) configure cmake to local install/build grpc
# include(FetchContent)
# set(ABSL_ENABLE_INSTALL ON)
# FetchContent_Declare(
#   gRPC
#   GIT_REPOSITORY https://github.com/grpc/grpc
#   GIT_TAG        v1.55.1
# )
# set(FETCHCONTENT_QUIET OFF)
# FetchContent_MakeAvailable(gRPC)
# find_package(Protobuf REQUIRED)
# find_package(Threads REQUIRED)

# set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
# set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

# Include src as subdirectory
add_subdirectory(src)
