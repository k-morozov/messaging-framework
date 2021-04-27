function(generate_proto_files)

    include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-module.cmake)
    include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-generate.cmake)

    set(PATH_TO_PROTO include/protocol/proto)

    # GENERATE PROTOBUF FILES
    file(GLOB PROTOBUF_FILES "include/protocol/proto/*.proto")


    find_package(Protobuf REQUIRED)
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOBUF_FILES})

    # copy to ${CMAKE_BINARY_DIR}/proto
    set(PROTO_FILES ${PROTO_SRCS} ${PROTO_HDRS})
    add_custom_target(protobuf_cpp_src_files ALL DEPENDS ${PROTO_FILES})
    add_custom_command(TARGET protobuf_cpp_src_files PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${PROTO_FILES} ${CMAKE_BINARY_DIR}/proto
            )

endfunction()