function(generate_proto_files)

    include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-module.cmake)
    include(${CONAN_LIB_DIRS_PROTOBUF}/cmake/protobuf/protobuf-generate.cmake)

    set(PATH_TO_PROTO include/protocol/proto)

    # GENERATE PROTOBUF FILES
    file(GLOB PROTOBUF_FILES "include/protocol/proto/*.proto")

    find_package(Protobuf REQUIRED)
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOBUF_FILES})

    # copy to ${CMAKE_BINARY_DIR}/proto
    add_custom_target(protobuf_cpp_src_files ALL DEPENDS ${PROTO_SRCS})
    add_custom_command(TARGET protobuf_cpp_src_files POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${PROTO_SRCS} ${CMAKE_BINARY_DIR}/proto
            )

    add_custom_target(protobuf_cpp_hdr_files ALL DEPENDS ${PROTO_HDRS})
    add_custom_command(TARGET protobuf_cpp_hdr_files POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${PROTO_HDRS} ${CMAKE_BINARY_DIR}/proto
            )

endfunction()