cmake_minimum_required(VERSION 3.28)

project(wisp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)

# Source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

include_directories(include)

# Executable setup
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Output directory
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target
)

# Create target directory and symlink if not exists
execute_process(
    COMMAND sh -c "mkdir -p ../target && ln -sf ../assets/personal-data ../target"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Find and link OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Fetch and include nlohmann_json and mINI
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY  https://github.com/nlohmann/json.git
    GIT_TAG         v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    mINI
    GIT_REPOSITORY  https://github.com/pulzed/mINI.git
    GIT_TAG         master
)
FetchContent_MakeAvailable(mINI)

# Libraries include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${nlohmann_json_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${mINI_SOURCE_DIR}/src)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENSSL_LIBRARIES} nlohmann_json mINI)
