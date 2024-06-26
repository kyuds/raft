# generate proto files
include(cmake/proto.cmake)

add_executable(raft
    cli.cc
    raft.h
    raft.cc
    rpc.h
    rpc.cc
    state.h
    state.cc
    timedcycle.h
    timedcycle.cc
    config.h
    config.cc
    utils.h
    utils.cc
)

target_include_directories(raft PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
)

# include json parser for ConfigParser
FetchContent_Declare(json URL ${JSON_LIB})
FetchContent_MakeAvailable(json)
FetchContent_Declare(plog URL ${PLOG_LIB})
FetchContent_MakeAvailable(plog)

target_link_libraries(raft
    PUBLIC
        grpc_proto
    PRIVATE
        ${JSON_LIB_LINK}
        plog
)
