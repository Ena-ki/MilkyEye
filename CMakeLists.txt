cmake_minimum_required(VERSION 4.2)
project(MilkyEye LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdParty/glfw)


file(GLOB_RECURSE SOURCE_FILES false "src/*.cpp" "src/*.c")
add_executable(MilkyEye ${SOURCE_FILES})

target_include_directories(MilkyEye PRIVATE 
    src 
    src/include 
    thirdParty/glfw/include
)

target_link_libraries(MilkyEye PRIVATE glfw)
