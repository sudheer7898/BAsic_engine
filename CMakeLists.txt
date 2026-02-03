cmake_minimum_required(VERSION 3.10.0)
project(BAsic_engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

find_package(assimp REQUIRED)

find_package(OpenGL REQUIRED)

add_library(glad third_party/glad/src/glad.c)

target_include_directories(glad PUBLIC third_party/glad/include)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.hpp")
add_library(BAsic_engine ${SOURCES} ${HEADERS})

target_link_libraries(BAsic_engine glad glfw OpenGL::GL assimp::assimp)
target_include_directories(BAsic_engine PRIVATE third_party/glad/include)