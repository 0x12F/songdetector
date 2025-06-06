cmake_minimum_required(VERSION 3.10)
project(SongDetector)

set(CMAKE_CXX_STANDARD 17)

find_package(JNI REQUIRED)

add_library(SongDetector SHARED SongDetector.cpp)

target_include_directories(SongDetector PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(SongDetector PRIVATE user32 windowsapp)
target_compile_options(SongDetector PRIVATE /await) 