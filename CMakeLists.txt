cmake_minimum_required(VERSION 3.10)

project(Messaging-framework CXX)
set(PROTOCOL_LIB_NAME protocol_lib)

# configure conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# generate from proto files
include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-module.cmake)
include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-generate.cmake)

file(GLOB PROTOBUF_FILES "proto/*.proto")
file(GLOB FILES "protocol/*.h" "protocol/*.cpp")

find_package(Protobuf REQUIRED)

set(OLD_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR}/proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOBUF_FILES})
set(CMAKE_CURRENT_BINARY_DIR  ${OLD_BINARY_DIR})
unset(OLD_BINARY_DIR)


add_library(${PROTOCOL_LIB_NAME} STATIC ${FILES} ${PROTO_SRCS} ${PROTO_HDRS})

set_target_properties(${PROTOCOL_LIB_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_compile_options(${PROTOCOL_LIB_NAME} PRIVATE "-fPIC")
target_link_libraries(${PROTOCOL_LIB_NAME}
        PUBLIC
#        ${CONAN_LIBS}
        ${CONAN_LIBS_PROTOBUF}
#        ${CONAN_SYSTEM_LIBS_PROTOBUF}
)

include_directories(
        protocol
        ${CMAKE_BINARY_DIR}
)

target_include_directories(${PROTOCOL_LIB_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_BINARY_DIR}
#            ${CMAKE_CURRENT_BINARY_DIR}
)

include(CTest)
enable_testing()

add_subdirectory(test)
#install(TARGETS ${PROTOCOL_LIB_NAME} DESTINATION /usr/local/lib)