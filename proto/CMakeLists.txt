cmake_minimum_required(VERSION 3.10)

include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-module.cmake)
include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-generate.cmake)

# GENERATE PROTOBUF FILES
file(GLOB PROTOBUF_FILES "*.proto")

find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOBUF_FILES})

add_library(generateProto STATIC ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(generateProto PUBLIC ${CMAKE_BINARY_DIR})
#target_link_libraries(generateProto ${CONAN_LIB_DIRS_PROTOBUF})