cmake_minimum_required(VERSION 3.22)

project(wisp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
include_directories(include)
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

execute_process(COMMAND sh -c "ln -s ../assets/help-text ../target"
        COMMAND sh -c "ln -s ../assets/personal-data ../target"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}openssl ${OPENSSL_LIBRARIES})

add_subdirectory(lib/nlohmann)
target_link_libraries(${PROJECT_NAME}nlohmann PRIVATE nlohmann_json::nlohmann_json)

