cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


project(
  MilkyEye
  VERSION 0.0.0
)

add_subdirectory(thirdParty/glfw)

add_executable(MilkyEye src/main.cpp src/glad.c) 

target_include_directories(
  MilkyEye
  PRIVATE src/include/
)

target_link_libraries(
  MilkyEye
  PRIVATE glfw
)
