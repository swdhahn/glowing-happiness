cmake_minimum_required(VERSION 3.19.2)

project(Program)

file(GLOB_RECURSE program_sources CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${program_sources})


# This stuff below adds OpenGL and Glfw to build project

find_package(OpenGL REQUIRED)

include_directories(libs/glew-2.1.0/include)
include_directories(libs/glfw-3.3.4/include)
include_directories(libs/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3.4)
add_subdirectory(libs/glew-2.1.0)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} glfw ${GLFW_LIBRARIES} glew_s ${GLEW_LIBRARIES})