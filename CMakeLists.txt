cmake_minimum_required(VERSION 3.23)
project(engine)

set(CMAKE_CXX_STANDARD 23)

link_directories(/opt/homebrew/lib)
include_directories(/opt/homebrew/include)

add_executable(engine main.cpp engine.cpp engine.h window.cpp window.h shader.cpp shader.h)
find_package(OpenGL REQUIRED)
target_link_libraries(engine OpenGL::GL)
find_package(GLEW REQUIRED)
target_link_libraries(engine GLEW::GLEW)
target_link_libraries(engine glfw)
