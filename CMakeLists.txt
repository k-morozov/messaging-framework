cmake_minimum_required(VERSION 3.10)

project(Messaging-framework VERSION 0.1.1)
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

include(cmake/generate_proto.cmake)

add_library(${PROTOCOL_LIB_NAME} STATIC ${FILES} ${PROTO_SRCS} ${PROTO_HDRS})
unset(FILES)
set_target_properties(${PROTOCOL_LIB_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_compile_options(${PROTOCOL_LIB_NAME} PRIVATE "-fPIC")
conan_target_link_libraries(${PROTOCOL_LIB_NAME})

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

if (NOT WIN32)
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_CONTACT morozov-kst@yandex.ru)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    include(CPack)
endif()

install(TARGETS ${PROTOCOL_LIB_NAME}
        DESTINATION
            "/usr/local/lib/goodok")

file(GLOB HDRS "protocol/*.h")
install(FILES ${HDRS} DESTINATION "/usr/local/include/goodok/protocol" COMPONENT devel)
install(FILES ${PROTO_HDRS} DESTINATION "/usr/local/include/goodok/protocol/proto" COMPONENT devel)
#@TODO CPACK_DEBIAN_PACKAGE_DEPENDS not set, the package will have no dependencies.