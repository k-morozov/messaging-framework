cmake_minimum_required(VERSION 3.10)

set(APP_NAME ut_messaging)
set(CONAN_DISABLE_CHECK_COMPILER TRUE)
conan_check_compiler()
add_executable(${APP_NAME} main.cpp testRequest.cpp)

include_directories(${CONAN_INCLUDE_DIRS_GTEST})
target_link_libraries(${APP_NAME}
        protocol_lib
        ${CONAN_LIBS_GTEST}
)

set_target_properties(${APP_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

add_test(NAME ${APP_NAME} COMMAND $<TARGET_FILE:${APP_NAME}>)