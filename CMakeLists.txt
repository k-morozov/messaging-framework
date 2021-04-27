cmake_minimum_required(VERSION 3.10)

project(Messaging-framework)

# configure conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# generate from proto files
add_subdirectory(proto ${CMAKE_BINARY_DIR}/proto)

# generate protocol library
add_subdirectory(protocol)

#install(TARGETS ${PROTOCOL_LIB_NAME} DESTINATION /usr/local/lib)