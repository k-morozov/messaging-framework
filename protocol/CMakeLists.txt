cmake_minimum_required(VERSION 3.10)

# build project
set(PROTOCOL_LIB_NAME protocol_lib)

file(GLOB FILES "*.h" "*.cpp")
add_library(${PROTOCOL_LIB_NAME} STATIC ${FILES})

set_target_properties(${PROTOCOL_LIB_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROTOCOL_LIB_NAME} PRIVATE "-fPIC")
target_link_libraries(${PROTOCOL_LIB_NAME}
        PUBLIC
            ${CONAN_LIBS}
            ${CONAN_SYSTEM_LIBS_PROTOBUF}
            generateProto
)

include_directories(
        ${CONAN_LIB_DIRS_PROTOBUF}
        ${CONAN_BIN_DIRS_PROTOBUF}
)

#message(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROTOCOL_LIB_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
#            ${CMAKE_SOURCE_DIR}
)