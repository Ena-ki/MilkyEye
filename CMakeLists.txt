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

add_executable(MilkyEye 
  src/main.cpp 
  src/glad.c
  src/process.cpp
  src/process.h
) 

target_include_directories(
  MilkyEye
  PRIVATE src/include/
)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(X11 REQUIRED)

target_link_libraries(
  MilkyEye PRIVATE 
  glfw
  OpenGL::GL
  Threads::Threads
  X11::X11
  X11::Xrandr
  X11::Xi
  ${CMAKE_DL_LIBS} 
)
