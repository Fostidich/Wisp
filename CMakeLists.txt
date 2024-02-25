cmake_minimum_required(VERSION 3.22)

project(wisp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "lib/*.cpp" "lib/*.c")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h" "lib/*.hpp" "lib/*.h")

include_directories(include lib)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

execute_process(COMMAND sh -c "ln -s ../assets/help-text ../target 2>/dev/null"
        COMMAND sh -c "ln -s ../assets/personal-data ../target 2>/dev/null"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})

