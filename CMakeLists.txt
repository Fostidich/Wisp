cmake_minimum_required(VERSION 3.22)

project(wisp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

include_directories(include)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS}
        src/utils/files.cpp
        include/utils/files.h
        src/commands/glob/glob.cpp
        include/commands/glob/glob.h
        src/commands/set/set.cpp
        include/commands/set/set.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target
)

target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
