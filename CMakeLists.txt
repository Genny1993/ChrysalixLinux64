cmake_minimum_required(VERSION 3.30.8)

set(CMAKE_CXX_COMPILER g++)

project(chrysalix VERSION 0.2.6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -funroll-loops -flto")

include_directories(src)
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(chrysalix ${SRC_FILES})

target_compile_options(chrysalix PRIVATE -Wall -Wextra -Wpedantic)
