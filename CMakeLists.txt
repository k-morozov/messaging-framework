cmake_minimum_required(VERSION 3.16)

project(Messaging-framework)

# configure conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# generate from proto files
include(cmake/generate_proto_files.cmake)
generate_proto_files()

# build project
set(PROTOCOL_LIB_NAME protocol_lib)

add_library(${PROTOCOL_LIB_NAME} STATIC)
file(GLOB ProtoFilesSrc "${CMAKE_BINARY_DIR}/proto/*.pb.cc")
file(GLOB ProtoFilesHdr "${CMAKE_BINARY_DIR}/proto/*.pb.h")

message(${ProtoFilesSrc})
message(${ProtoFilesHdr})

target_sources(${PROTOCOL_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/protocol/protocol.h
    PRIVATE
        ${ProtoFilesSrc}
        ${ProtoFilesHdr}
        "include/protocol/command_table.h"
        "include/protocol/datetime.h" include/protocol/datetime.cpp
        "include/protocol/msgfactory.h" include/protocol/msgfactory.cpp
)

set_target_properties(${PROTOCOL_LIB_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROTOCOL_LIB_NAME} PRIVATE "-fPIC")
target_link_libraries(${PROTOCOL_LIB_NAME}
    PUBLIC
        ${CONAN_LIBS}
        ${CONAN_SYSTEM_LIBS_PROTOBUF}
)

include_directories(
        ${CONAN_LIB_DIRS_PROTOBUF}
        ${CONAN_BIN_DIRS_PROTOBUF}
)

target_include_directories(${PROTOCOL_LIB_NAME}
    PUBLIC
        ./include
        ${CONAN_LIB_DIRS_PROTOBUF}
        ${CONAN_BIN_DIRS_PROTOBUF}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

#install(TARGETS ${PROTOCOL_LIB_NAME} DESTINATION /usr/local/lib)